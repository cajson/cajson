#include <gen1.c>

// array = [ expr* ]
static void gen_array(link_t *head) {
    emit("[");
    gen_list(head, ",");
    emit("]");
}

static void gen_str(node_t *node) {
    gen_token(node);
}


static void gen_pair(node_t *n1, node_t *n2) {
    gen_code(n1);
    emit(":");
    gen_code(n2);
}

// map = [ (expr:expr)* ]
static void gen_map(link_t *head) {
    emit("{");
    gen_list(head, ",");
    emit("}");
}
