typedef struct node_t {
  char type;
  union {
    struct node_t *node;
    sym_t *sym;
  };
  union {
    struct node_t *next;
    struct node_t *node2;
  };
} node_t;

#define NNODE 100000
node_t nodes[NNODE];
int nodeTop = 0;

node_t *node(char type) {
    node_t *n = &nodes[nodeTop++];
    n->type = type;
    n->next = NULL;
}

node_t *op1(char op, node_t *n1) {
    node_t *n = node(op);
    n->node = n1;
    return n;
}

node_t *op2(char op, node_t *n1, node_t *n2) {
    node_t *n = node(op);
    n->node = n1;
    n->node2 = n2;
    return n;
}

