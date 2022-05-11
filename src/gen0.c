#include "cj.h"

static int stack[1000];
static int top = 0;
static int block_level = 0;
static int fn_level = 0;
static bool show_line = true;

#define emit(...) { debug(__VA_ARGS__); if (ofp) fprintf(ofp, __VA_ARGS__); }
#define line(i) if (show_line) emit("/* %-3d*/\t", i);

static void gen_str(node_t *node);
static void gen_num(node_t *node);
static void gen_id(node_t *node);
static void gen_op0(int op);
static void gen_op1(int op, node_t *node);
static void gen_op2(node_t *node1, int op, node_t *node2);
static void gen_term(node_t *pid, link_t *head);
static void gen_pid(node_t *pid);
static void gen_params(link_t *head);
static void gen_array(link_t *head);
static void gen_pair(node_t *n1, node_t *n2);
static void gen_map(link_t *head);
static void gen_args(link_t *head);
static void gen_assign(node_t *pid, node_t *type, node_t *exp);
static void gen_return(int op, node_t *exp);
static void gen_import(node_t *id1, node_t *id2);
static void gen_while(node_t *exp, node_t *stmt);
static void gen_if(node_t *exp, node_t *stmt1, node_t *stmt2);
static void gen_for_in(node_t *id, node_t *exp, node_t *stmt);
static void gen_for_of(node_t *id, node_t *exp, node_t *stmt);
static void gen_for_to(node_t *id, node_t *from, node_t *to, node_t *step, node_t *stmt);
static void gen_function(node_t *id, node_t *params, node_t *block);
static void gen_block(node_t *block);
static void gen_stmts(node_t *node);
static void gen_stmt(node_t *stmt);
static void gen_code(node_t *me);

static void indent(int level) {
    emit("%*s", level*2, "");
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

static void gen_token(node_t *node) {
    emit("%.*s", node->ptk->len, node->ptk->str);
}

static void gen_list(link_t *head, char *spliter) {
    for (link_t *p = head; p != NULL; p = p->next) {
        gen_code(p->node);
        if (p->next != NULL) emit("%s", spliter);
    }
}

static void gen_code(node_t *me) {
    node_t **args;
    if (me == NULL) return;
    int type = me->type;
    args = me->array;
    if (type == Stmts) {
        gen_stmts(me);
    } else if (type == Stmt) {
        gen_stmt(me);
    } else if (type == Block) {
        push(Block); block_level++;
        gen_block(me);
        pop(Block);  block_level--;
    } else if (type == Import) {
        gen_import(args[0], args[1]);
    } else if (type == While) {
        push(While);
        gen_while(args[0], args[1]);
        pop(While);
    } else if (type == If) {
        push(If);
        gen_if(args[0], args[1], args[2]);
        pop(If);
    } else if (type == ForIn) {
        push(ForIn);
        gen_for_in(args[0], args[1], args[2]);
        pop(ForIn);
    } else if (type == ForOf) {
        push(ForOf);
        gen_for_of(args[0], args[1], args[2]);
        pop(ForOf);
    } else if (type == ForTo) {
        push(ForTo);
        gen_for_to(args[0], args[1], args[2], args[3], args[4]);
        pop(ForTo);
    } else if (type == Function) {
        push(Function); fn_level++;
        gen_function(args[0], args[1], args[2]);
        pop(Function);  fn_level--;
    } else if (type == Return || type == '?') {
        gen_return(type, args[0]); // gen_return(type, me->node);
    } else if (type == Continue || type == Break) {
        gen_op0(type); 
    } else if (type == Params) { // params = (param)*
        gen_params(me->list->head);
    } else if (type == Array) {
        gen_array(me->list->head);
    } else if (type == Map) {
        gen_map(me->list->head);
    } else if (type == Args) { // args  = ( expr* )
        gen_args(me->list->head);
    } else if (type == Term) { // term =  pid ([expr] | . id | args )*
        link_t *head = me->list->head;
        node_t *id = head->node;
        gen_term(id, head->next);
    } else if (type == Pid) { // pid = (@|$)? id
        gen_pid(me);
    } else if (type==Assign) {
        gen_assign(args[0], args[1], args[2]);
    } else if (type == Pair) {
        gen_pair(args[0], args[1]);
    } else if (type == Token) {
        gen_token(me);
    } else if (me->len == 0) { // op0 或 type 中的 * ...
        gen_op0(type);
    } else if (me->len == 1) { // (is_op1(type)) 不能用，因為 type 中可能出現該運算
        gen_op1(type, args[0]);
    } else if (me->len == 2) { // (is_op2(type)) 不能用，因為 type 中可能出現該運算
        gen_op2(args[0], type, args[1]);
    } else if (type==Id) {
        gen_id(me);
    } else if (type==Num) {
        gen_num(me);
    } else if (type==Str) {
        gen_str(me);
    } else {
        error("gen_code:unknown type=%d=%c", type, type);
    }
}
