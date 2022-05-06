node_t *expr();
node_t *block();
node_t *params();

node_t *base(int type) {
    token_t t = skip(type);
    node_t *r = node(type);
    r->sym = t.sym;
    return r;
}

node_t *id() {
    return base(Id);
}

node_t *str() {
    return base(Str);
}

node_t *num() {
    return base(Num);
}

node_t *exp_list(int type, char lpair, char rpair) {
    node_t *r = node(type);
    r->list = list();
    skip(lpair);
    while (tk.type != rpair) {
        list_add(r->list, expr());
        if (tk.type == ',') next();
    }
    skip(rpair);
    list_reverse(r->list);
    return r;
}

// args = (expr*)
node_t *args() {
    return exp_list(Args, '(', ')');
}

// array = [ expr* ]
node_t *array() {
    return exp_list(Array, '[', ']');
}

// pid = (@|$)? id
node_t *pid() {
    int pre = None;
    if (strchr("@$", tk.type))
        pre = next().type;
    node_t *nid = id();
    return (pre==None)?nid:op1(pre, nid);
}

// term = pid ( [expr] | . id | args )*
node_t *term() {
    node_t *r = node(Term);
    r->list = list();
    list_add(r->list, pid());
    while (strchr("[.(", tk.type)) {
        if (tk.type == '[') { // array member
            next();
            node_t *e=expr();
            skip(']');
            list_add(r->list, op1('[', e));
        } else if (tk.type == '.') { // object member
            next();
            node_t *mid = id();
            list_add(r->list, op1('.', mid));
        } else if (tk.type == '(') { // function call
            list_add(r->list, args());
        }
    }
    list_reverse(r->list);
    return r;
}

// factor = (!-~) (factor) | Num | (expr) | term
node_t *factor() {
    if (strchr("!-~", tk.type)) {
        int op = (tk.type=='-')?Neg:tk.type;
        next();
        return op1(op, factor());
    } else if (tk.type == Num) {
        return num();
    } else if (tk.type == '(') { // ( expr )
        skip('(');
        node_t *e = expr();
        skip(')');
        return e;
    } else {
        return term();
    }
}

// map = 'map' { (expr:expr)* }
node_t *map() {
    node_t *r = node(Map);
    r->list = list();
    // skip_str("map");
    skip('{');
    while (tk.type != '}') {
        node_t *e1 = expr();
        skip(':');
        node_t *e2 = expr();
        list_add(r->list, pair(e1, e2));
        if (tk.type == ',') next();
    }
    skip('}');
    list_reverse(r->list);
    return r;
}

// item = Str | fn | array | map | factor
node_t *item() {
    if (tk.type == Str) {
        return str();
    } else if (match("fn")) { // fn (params) block
        next();
        skip('(');
        node_t *p1 = params();
        skip(')');
        node_t *b1 = block();
        return op2(Function, p1, b1);
    } else if (tk.type == '{') { // if (match("map")) { // map
        return map();
    } else if (tk.type == '[') { // array
        return array();
    } else {
        return factor();
    }
}

// expr = item (op2 expr)?
node_t *expr() {
    node_t *r = item();
    if (is_op2(tk.type)) {
        token_t op = next();
        node_t *e = expr();
        r = op2(op.type, r, e);
    }
    return r;
}

// type = ('int|float|str|array|map|object') '*'*
node_t *type() {
    char *types[]={"int", "float", "str", "array", "map", "object"};
    if (member(types, size(types))) {
        node_t *r = node(Type);
        r->list = list();
        node_t *nid = id();
        list_add(r->list, nid);
        while (tk.type == '*') list_add(r->list, op0('*'));
        list_reverse(r->list);
        return r;
    }
    return NULL;
}

// assign = pid(:type)?= expr
node_t *assign() {
    scan_save();
    if (strchr("@$", tk.type) || tk.type == Id) {
        node_t *nid = pid(), *t = NULL, *e = NULL;
        if (tk.type == ':') {
            next();
            t = type();
        }
        if (tk.type=='=') {
            next();
            e = expr();
        }
        if (e /*=expr*/ || strchr(",)", tk.type) /*params*/)
            return op3(Assign, nid, t, e);
    }
    scan_restore();
    return NULL;
}

// params = (assign*)
node_t *params() {
    node_t *r = node(Params);
    r->list = list();
    while (tk.type != ')') { 
        list_add(r->list, assign());
        if (tk.type == ',') next();
    }
    list_reverse(r->list);
    return r;
}

// stmt = block                     |
//        while expr stmt           | 
//        if expr stmt (else stmt)? |
//        for id (in|of) expr stmt  |
//        for id=expr to expr step expr stmt |
//        return expr               |
//        continue                  |
//        break                     |
//        assign
node_t *stmt() {
    node_t *e, *s, *r=node(Stmt);
    if (tk.type == '{') { // block
        return block();
    } else if (match("while")) { // while expr stmt
        next();
        e = expr();
        s = stmt();
        r->node = op2(While, e, s);
    } else if (match("if")) { // if expr stmt (else stmt)?
        next();
        e = expr();
        s = stmt();
        node_t *s2 = NULL;
        if (match("else")) {
            next();
            s2 = stmt();
        }
        r->node = op3(If, e, s, s2);
    } else if (match("for")) { // for id in expr stmt
        next();
        node_t *nid = id();
        if (match("in") || match("of")) {
            token_t optk = next();
            int op = (tk_match(optk, "in"))?ForIn:ForOf;
            e = expr();
            s = stmt();
            r->node = op3(op, nid, e, s);
        } else if (match("=")) {
            next();
            node_t *step=NULL, *from, *to;
            from = expr();
            skip_str("to");
            to = expr();
            if (match("step")) {
                next();
                step = expr();
            }
            s = stmt();
            r->node = op5(ForTo, nid, from, to, step, s);
        }
    } else if (match("return") || tk.type == '?') { // ?exp = return exp
        next();
        e = expr();
        r->node = op1(Return, e);
    } else if (match("continue")) { // continue
        next();
        r->node = op0(Continue);
    } else if (match("break")) { // break
        next();
        r->node = op0(Break);
    } else {
        r->node = assign();
        if (!r->node) r->node = expr();
    }
    return r;
}

// stmts = stmt*
node_t *stmts() {
    node_t *r = node(Stmts);
    r->list = list();
    while (tk.type != End && tk.type != '}') {
        list_add(r->list, stmt());
    }
    list_reverse(r->list);
    return r;
}

// block = { stmts }
node_t *block() {
    node_t *r = node(Block);
    skip('{');
    r->node = stmts();
    skip('}');
    return r;
}

// program = stmts
node_t *parse(char *source) {
    p = source;
    next();
    return stmts();
}
