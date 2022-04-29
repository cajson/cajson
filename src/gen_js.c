void gen_comment(char *text) {
    emit("// ");
    emit(text);
}

void gen_sym(node_t *node) {
    emit("%.*s", node->sym->len, node->sym->name);
}

void gen_code(node_t *node) {
    if (node == NULL) return;
    char type = node->type;
    if (type == Stmts) {
        gen_code(node->node);
        gen_code(node->next);
    } else if (is_op2(type)) {
        emit("(");
        gen_code(node->node);
        emit("%c", type);
        gen_code(node->node2);
        emit(")");
//    } else if (is_op1(type)) {
//        emit("%c", type);
//        gen_code(node->node1);
    } else if (type=='=') {
        gen_code(node->node);
        emit("=");
        gen_code(node->node2);
        emit(";\n");
    } else if (type==Id || type==Num || type==Str) {
        gen_sym(node);
    } else {
        error("unknown node->type=%d=%c");
    }
}