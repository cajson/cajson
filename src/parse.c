node_t *expr();
node_t *block();
node_t *params();
node_t *function();

node_t *base(int type) {
    node_t *r = node(type);
    skip(type);
    return r;
}

node_t *key(int k) {
    return op1(Key, base(k));
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

node_t *tok() {
    node_t *n = node(Token);
    next();
    return n;
}

node_t *tk_list(int type, char *end) {
    node_t *r = node(type);
    r->list = list();
    while (tk != End && !contain(end, tk)) {
        list_add(r->list, tok());
        // next();
    }
    list_reverse(r->list);
    return r;
}

node_t *exp_list(int type, char lpair, char rpair) {
    node_t *r = node(type);
    r->list = list();
    skip(lpair);
    while (tk != rpair) {
        list_add(r->list, expr());
        if (tk == ',') next();
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
    node_t *r = node(Pid);
    int pre = None;
    if (tk == '@') { pre = Global; next(); }
    else if (tk == '$') { pre = This; next(); }
    node_t *nid = id();
    r->node = op1(pre, nid);
    return r;
}

// term = (await|new)? pid ( [expr] | . id | args )*
node_t *term() {
    node_t *r = node(Term);
    r->list = list();
    if (tk == Await || tk == New)
        list_add(r->list, key(tk));
    list_add(r->list, pid());
    while (contain("[.(", tk)) {
        if (tk == '[') { // array member
            next();
            node_t *e=expr();
            skip(']');
            list_add(r->list, op1('[', e));
        } else if (tk == '.') { // object member
            next();
            node_t *mid = id();
            list_add(r->list, op1('.', mid));
        } else if (tk == '(') { // function call
            list_add(r->list, args());
        }
    }
    list_reverse(r->list);
    return r;
}

// factor = (!-~) (factor) | Num | (expr) | term
node_t *factor() {
    if (contain("!-~", tk)) {
        int op = (tk=='-')?Neg:tk;
        next();
        return op1(op, factor());
    } else if (tk == Num) {
        return num();
    } else if (tk == '(') { // ( expr )
        skip('(');
        node_t *e = expr();
        skip(')');
        return e;
    } else {
        return term();
    }
}

// map = { (id|str):expr)* }
node_t *map(int type) {
    node_t *r = node(type); // node(Map);
    r->list = list();
    skip('{');
    while (tk != '}') {
        node_t *key = (tk == Id) ? id() : str(); // expr();
        skip(':');
        node_t *e2 = expr();
        list_add(r->list, pair(key, e2));
        if (tk == ',') next();
    }
    skip('}');
    list_reverse(r->list);
    return r;
}

// item = Str | array | function | map | factor
node_t *item() {
    if (tk == Str) {
        return str();
    } else if (tk == '[') { // array
        return array();
    } else if (tk == Fn) {
        return function();
    } else if (tk == '{' || tk == Class || tk == Object || tk == Map) { // if (match("map")) { // map
        int type = tk;
        if (tk == '{') type = Object; else next();
        return map(type);
    } else {
        return factor();
    }
}

// expr = item (op2 expr)?
node_t *expr() {
    node_t *r = item();
    if (is_op2(tk)) {
        token_t op = next();
        node_t *e = expr();
        r = op2(op.tk, r, e);
    }
    return r;
}

// type = id**
node_t *type() {
    return tk_list(Type, "=),");
}

// assign = term(:type?)?(= expr)?
node_t *assign() {
    node_t *n = item(), *t = NULL, *e = NULL;
    if (tk == ':') { // 如果沒有 : ，會傳回 NULL
        next();
        t = type(); // 如果是空的，會傳回 node with empty list
    }
    if (tk=='=') {
        next();
        e = expr();
    }
    return op3(Assign, n, t, e);
}

// params = (assign*)
node_t *params() {
    node_t *r = node(Params);
    r->list = list();
    while (tk != ')') { 
        list_add(r->list, assign());
        if (tk == ',') next();
    }
    list_reverse(r->list);
    return r;
}

// function = fn id?(params) block
node_t *function() {
    skip(Fn);
    node_t *nid = (tk==Id) ? id() : NULL;
    skip('(');
    node_t *p1 = params();
    skip(')');
    node_t *b1 = block();
    return op3(Function, nid, p1, b1);
}
// stmt = block                     |
//        while expr stmt           | 
//        if expr stmt (else stmt)? |
//        for id (in|of) expr stmt  |
//        for id=expr to expr step expr stmt |
//        return expr               |
//        continue                  |
//        break                     |
//        term(:type?)?= expr
node_t *stmt() {
    node_t *e, *s, *r=node(Stmt);
    if (tk == '{') { // block
        return block();
    } else if (tk == Import) { // import name as id
        next();
        node_t *str1, *id2;
        str1 = str();
        if (tk == As) {
            next();
            id2 = id();
        }
        r->node = op2(Import, str1, id2);
    } else if (tk == While) { // while expr stmt
        next();
        e = expr();
        s = stmt();
        r->node = op2(While, e, s);
    } else if (tk == If) { // if expr stmt (else stmt)?
        next();
        e = expr();
        s = stmt();
        node_t *s2 = NULL;
        if (tk == Else) {
            next();
            s2 = stmt();
        }
        r->node = op3(If, e, s, s2);
    } else if (tk == For) { // for id in expr stmt
        next();
        node_t *nid = id();
        // if (tk == ':') next();
        if (tk == In || tk == Of) {
            token_t opt = next();
            int op = (opt.tk == In)?ForIn:ForOf;
            e = expr();
            s = stmt();
            r->node = op3(op, nid, e, s);
        } else if (tk == ':') {
            skip(':');
            skip('=');
            node_t *step=NULL, *from, *to;
            from = expr();
            skip(To);
            to = expr();
            if (tk == Step) {
                next();
                step = expr();
            }
            s = stmt();
            r->node = op5(ForTo, nid, from, to, step, s);
        }
    } else if (tk == Return || tk == '?') { // ?exp = return exp
        token_t t = next();
        e = expr();
        int op = (t.tk == '?') ? '?' : Return;
        r->node = op1(op, e);
    } else if (tk == Continue || tk == Break) {
        token_t t = next();
        next();
        r->node = op0(t.tk);
    } else { // term(:type?)?(= expr)?
        r->node = assign();
        // if (!r->node) r->node = expr();
    }
    return r;
}

// stmts = stmt*
node_t *stmts() {
    node_t *r = node(Stmts);
    r->list = list();
    while (tk != End && tk != '}') {
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
