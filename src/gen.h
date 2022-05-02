#define emit(...) { printf(__VA_ARGS__); sprintf(e, __VA_ARGS__); e+=strlen(e); }

static void gen_code(node_t *me);
static void gen_list(link_t *head);
static void gen_sym(node_t *node);
static void gen_indent(int n);
static int level;