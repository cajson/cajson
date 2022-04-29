token_t skip(int t) {
    token_t r = tk;
    if (tk.type==t)
        next();
    else
        error("skip type=%d=%c, but got a %d\n", t, t, tk.type);
    return r;
}

bool match(char *str) {
    int len = strlen(str);
    return len == tk.len && memcmp(str, tk.str, len)==0;
}

token_t tk0; char *p0;
void scan_save() { tk0 = tk; p0=p; }
void scan_restore() { tk = tk0; p=p0; }

node_t *expr();

// ITEM = number | string | id | (EXP)
node_t *item() {
    token_t t=tk;
    node_t *n;
    if (t.type == Id || t.type == Num || t.type == Str) {
        next();
        n = node(Id);
        n->sym = t.sym;
    } else if (t.type == '(') {
        skip('(');
        n = expr();
        skip(')');
    } else {
        error("item start with type=%d=%c, str=%10s", t.type, t.type, t.str);
    }
    return n;
}

// TERM = [-~!]* ITEM ([EXP] | (EXP))*
node_t *term() {
    node_t *n = NULL, *tail = NULL;
    while (strchr("-~!", tk.type)) {
        n = op1(tk.type, n);
        if (n == NULL) tail = n;
        next();
    }
    node_t *it = item();
    while (strchr("[(", tk.type)) {
        token_t op = tk;
        it = op2(tk.type, it, expr());
        if (op.type == '[') skip(']'); else skip(')');
        next();
    }
    if (tail==NULL) n = it; else tail->node = it;
    return n;
}

// EXPR = TERM (op TERM)*
// op = +-*/....
node_t *expr() {
    node_t *n=term();
    while (is_op2(tk.type)) {
        token_t op = tk; next();
        node_t *n2 = term();
        n = op2(op.type, n, n2);
    }
    return n;
}

// STMT = (id=)?expr;
node_t *stmt() {
    token_t id;
    bool assign = false;
    if (tk.type == Id) {
        scan_save();
        id = skip(Id);
        if (tk.type == '=') {
            skip('=');
            assign = true;
        } else {
            scan_restore(); // 還原掃描點到 stmt 開頭
        }
    }
    node_t *n = expr();
    if (assign) {
        node_t *nid = node(Id);
        nid->sym = id.sym;
        n = op2('=', nid, n);
    }
    skip(';');
    return n;
}

// PROG = STMTS
node_t *stmts() {
    node_t *list = node(Stmts), *p=list;
    while (tk.type != None) {
        node_t *s = stmt();
        p->node = s;
        p->next = node(Stmts);
        p = p->next;
    }
    return list;
}

node_t *prog() {
    return stmts();
}

node_t *parse(char *source) {
    p = source;
    next();
    return prog();
}