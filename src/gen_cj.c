void gen_code(node_t *node);

void gen_comment(char *text) {
    emit("// ");
    emit(text);
}

void gen_sym(node_t *node) {
    emit("%.*s", node->sym->len, node->sym->name);
}

void gen_term(node_t *id, link_t *head) {
    link_t *p;
    gen_code(id);
    for (p=head; p != NULL; p = p->next) {
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
}

void gen_while(node_t *exp, node_t *stmt) {
    emit("while");
    gen_code(exp);
    gen_code(stmt);
}

void gen_if(node_t *exp, node_t *stmt1, node_t *stmt2) {
    
}

void gen_for(node_t *id, node_t *exp, node_t *stmt) {

}

void gen_function(node_t *params, node_t *stmts) {

}

void gen_stmts(node_t *node) {
    link_t *p = node->list->head;
    while (p != NULL) {
        gen_code(p->node);
        printf("\n");
        p = p->next;
    }
}

void gen_list(link_t *head) {
    for (link_t *p = head; p != NULL; p = p->next) {
        gen_code(p->node);
        emit(" ");
    }
}

void gen_code(node_t *me) {
    node_t **a;
    if (me == NULL) return;
    int type = me->type;
    // printf("type=%d\n", me->type);
    if (type == Stmts) {
        gen_stmts(me);
    } else if (type == Block) {
        emit("{");
        gen_stmts(me->node);
        emit("}");
    } else if (type == While) {
        node_t **nodes = me->array->nodes;
        gen_while(nodes[0], nodes[1]);
    } else if (type == If) {
        node_t **nodes = me->array->nodes;
        gen_if(nodes[0], nodes[1], nodes[2]);
    } else if (type == For) {
        node_t **nodes = me->array->nodes;
        gen_for(nodes[0], nodes[1], nodes[2]);
    } else if (type == Function) {
        node_t **nodes = me->array->nodes;
        gen_function(nodes[0], nodes[1]->node);
    } else if (type == Return) {
        emit("return");
        gen_code(me->node);
    } else if (type == Params) { // params = (id(=expr)?)*
        emit("(");
        gen_list(me->list->head);
        emit(")");
    } else if (type == Array) {
        emit("[");
        gen_list(me->list->head);
        emit("]");
    } else if (type == Args) { // args  = ( expr* )
        emit("(");
        gen_list(me->list->head);
        emit(")");
    } else if (type == Term) { // term =  id ([expr] | . id | args )*
        link_t *head = me->list->head;
        node_t *id = head->node;
        gen_term(id, head->next);
    } else if (is_op2(type)) {
        a = me->array->nodes;
        emit("(");
        gen_code(a[0]);
        emit("%c", type);
        gen_code(a[1]);
        emit(")");
    } else if (type=='=') {
        a = me->array->nodes;
        gen_code(a[0]);
        emit("=");
        gen_code(a[1]);
    } else if (type==Id) {
        gen_sym(me);
    } else if (type==Num || type==Str) {
        gen_sym(me);
    } else {
        error("unknown me->type=%d=%c");
    }
}