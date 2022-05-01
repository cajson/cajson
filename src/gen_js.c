void gen_comment(char *text) {
    emit("// ");
    emit(text);
}

void gen_sym(node_t *node) {
    emit("%.*s", node->sym->len, node->sym->name);
}

void gen_code(node_t *node) {
    node_t **a;
    if (node == NULL) return;
    int type = node->type;
    // printf("type=%d\n", node->type);
    if (type == Stmts) {
        link_t *p = node->list->head;
        while (p != NULL) {
            gen_code(p->node);
            printf("\n");
            p = p->next;
        }
    } else if (is_op2(type)) {
        a = node->array->nodes;
        emit("(");
        gen_code(a[0]);
        emit("%c", type);
        gen_code(a[1]);
        emit(")");
    } else if (type=='=') {
        a = node->array->nodes;
        gen_code(a[0]);
        emit("=");
        gen_code(a[1]);
        emit(";\n");
    } else if (type==Term) { // term =  id ([expr] | . id | args )*
        link_t *p = node->list->head; 
        node_t *id = p->node;
        gen_code(id);
        for (p=p->next; p != NULL; p = p->next) {
            node_t *n = p->node; int op = n->type; 
            if (op == '[') {
                emit("[");
                gen_code(n->node);
                emit("]");
            } else if (op == '.') {
                emit(".");
                gen_code(n->node);
            } else if (op == Args) {
                emit("(");
                gen_code(n);
                emit(")");
            }
        }
    } else if (type==Args) { // args  = ( expr* )
        for (link_t *p = node->list->head; p != NULL; p = p->next) {
            gen_code(p->node);
            emit(" ");
        }
    } else if (type==Id) {
        gen_sym(node);
    } else if (type==Num || type==Str) {
        gen_sym(node);
    } else {
        error("unknown node->type=%d=%c");
    }
}