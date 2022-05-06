#define emit(...) { printf(__VA_ARGS__); }

static void gen_code(node_t *me);
static void gen_list(link_t *head, char *spliter);
static void gen_sym(node_t *node);
static void push(int type);
static int  pop(int type);
static int  peek();
static void indent(int level);
static int  block_level, fn_level;
static int  stack[];
static int  top;
