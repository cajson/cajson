typedef struct node_t node_t;
typedef struct array_t array_t;
typedef struct link_t link_t;
typedef struct list_t list_t;

struct node_t {
  int type;
  union {
    list_t  *list;
    sym_t   *sym;
    node_t  *node;
    array_t *array;
  };
};

struct array_t {
  node_t **nodes;
  int len;
};

struct link_t {
  node_t *node;
  link_t *next;
};

struct list_t {
  int len;
  link_t *head;
};

#define NPTR 100000
void *pools[NPTR];
int poolTop = 0;

void *pool(int size) {
  void *p=malloc(size);
  memset(p, 0, size);
  if (!p) error("pool() alloc fail!");
  pools[poolTop++] = p;
  return p;
}

node_t *node(int type) {
    node_t *n = pool(sizeof(node_t));
    n->type = type;
    return n;
}

array_t *narray(node_t *nodes[], int len) {
    array_t *a = pool(sizeof(array_t));
    a->len = len;
    int size = sizeof(node_t*)*len;
    a->nodes = pool(size);
    memcpy(a->nodes, nodes, size);
    return a;
}

link_t *link() {
    return pool(sizeof(link_t));
}

list_t *list() {
    return pool(sizeof(list_t));
}

node_t *op1(int op, node_t *n1) {
    node_t *n = node(op);
    n->node = n1;
    return n;
}

node_t *op_n(int op, node_t *nodes[], int len) {
    node_t *n = node(op);
    n->array = narray(nodes, len);
    return n;
}

node_t *op2(int op, node_t *n1, node_t *n2) {
    node_t *a[] = { n1, n2 };
    return op_n(op, a, 2);
}

node_t *op3(int op, node_t *n1, node_t *n2, node_t *n3) {
    node_t *a[] = { n1, n2, n3 };
    return op_n(op, a, 3);
}

void list_add(list_t *list, node_t *node) {
    link_t *link = pool(sizeof(link_t));
    link->node = node;
    link->next = list->head;
    list->head = link;
    list->len ++;
}

// ref: https://www.geeksforgeeks.org/reverse-a-linked-list/
void list_reverse(list_t *list) {
    link_t* t=list->head, *prev=NULL, *next=NULL;
    while (t != NULL) {
        next = t->next; // Store next
        t->next = prev; // Reverse current node's pointer
        prev = t;       // Move pointers one position ahead.
        t = next;       // move to the next
    }
    list->head = prev;
}

void list_print(list_t *list) {
    for (link_t* t=list->head; t!=NULL; t=t->next) {
      printf("%p=>", t);
    }
}
