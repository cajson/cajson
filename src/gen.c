static void gen_sym(node_t *node) {
    emit("%.*s", node->sym->len, node->sym->name);
}

static void gen_list(link_t *head) {
    for (link_t *p = head; p != NULL; p = p->next) {
        gen_code(p->node);
        if (p->next != NULL) emit(" ");
    }
}

static void gen_code(node_t *me) {
    node_t **args;
    if (me == NULL) return;
    int type = me->type;
    if (type == Stmts) {
        gen_stmts(me);
    } else if (type == Stmt) {
        gen_stmt(me);
    } else if (type == Block) {
        gen_block(me);
    } else if (type == While) {
        args = me->array->nodes;
        gen_while(args[0], args[1]);
    } else if (type == If) {
        args = me->array->nodes;
        gen_if(args[0], args[1], args[2]);
    } else if (type == For) {
        args = me->array->nodes;
        gen_for(args[0], args[1], args[2]);
    } else if (type == Function) {
        args = me->array->nodes;
        gen_function(args[0], args[1]);
    } else if (type == Return) {
        gen_return(me->node);
    } else if (type == Params) { // params = (param)*
        gen_params(me->list->head);
    } else if (type == Param) { // param = id (:expr)?
        args = me->array->nodes;
        gen_param(args[0], args[1]);
    } else if (type == Array) {
        gen_array(me->list->head);
    } else if (type == Args) { // args  = ( expr* )
        gen_args(me->list->head);
    } else if (type == Term) { // term =  id ([expr] | . id | args )*
        link_t *head = me->list->head;
        node_t *id = head->node;
        gen_term(id, head->next);
    } else if (is_op2(type)) {
        args = me->array->nodes;
        gen_op2(args[0], type, args[1]);
    } else if (type=='=' || type == ':') {
        args = me->array->nodes;
        gen_assign(args[0], type, args[1]);
    } else if (type==Id) {
        gen_id(me);
    } else if (type==Num) {
        gen_num(me);
    } else if (type==Str) {
        gen_str(me);
    } else {
        error("gen_code:unknown type=%d=%c");
    }
}
