static int stack[1000];
static int top = 0;
static int block_level = 0;
static int fn_level = 0;

static void indent(int level) {
    // printf(" %3d %*s", level, level*2, "");
    printf("%*s", level*2, "");
}

static void push(int type) {
    stack[top++] = type;
}

static int pop(int type) {
    int p = stack[--top];
    if (p != type) error("pop %d!=%d\n", p, type);
    return type;
}

static int peek() {
    return stack[top-1];
}

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
        // push(Stmt);
        gen_stmt(me);
        // pop(Stmt);
    } else if (type == Block) {
        push(Block); block_level++;
        gen_block(me);
        pop(Block);  block_level--;
    } else if (type == While) {
        push(While);
        args = me->array->nodes;
        gen_while(args[0], args[1]);
        pop(While);
    } else if (type == If) {
        push(If);
        args = me->array->nodes;
        gen_if(args[0], args[1], args[2]);
        pop(If);
    } else if (type == ForIn) {
        push(ForIn);
        args = me->array->nodes;
        gen_for_in(args[0], args[1], args[2]);
        pop(ForIn);
    } else if (type == ForOf) {
        push(ForOf);
        args = me->array->nodes;
        gen_for_of(args[0], args[1], args[2]);
        pop(ForOf);
    } else if (type == ForTo) {
        push(ForTo);
        args = me->array->nodes;
        gen_for_to(args[0], args[1], args[2], args[3], args[4]);
        pop(ForTo);
    } else if (type == Function) {
        push(Function); fn_level++;
        args = me->array->nodes;
        gen_function(args[0], args[1]);
        pop(Function);  fn_level--;
    } else if (type == Return) {
        gen_return(me->node);
    } else if (type == Continue || type == Break) {
        gen_op0(type); 
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
/*    } else if (type == Item) { // item = Num | Str | function | array | block | ( expr ) | term
        push(Item);
        gen_item(me);
        pop(Item);*/
    } else if (is_op1(type)) {
        gen_op1(type, me->node);
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
