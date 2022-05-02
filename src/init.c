#define NMAX 100000
int src, debug, o_run, o_dump;
int line = 1;
// char data[NMAX], *datap=data;
char source[NMAX], *p=source, *lp=source;
char target[NMAX], *e=target, *le=target;

char *op_names[] = {
  "op1begin", "++", "--", "op1end",
  "op2begin", "||", "&&", "==", "!=", "<=", ">=", "<<", ">>", "op2end"
};

char* op_name(int op, char *name) {
  if (op < AsciiEnd)
    sprintf(name, "%c", (char) op);
  else if (op > Op1Begin && op < Op2End)
    sprintf(name, "%s", op_names[op-Op1Begin]);
  else
    error("op_name(%d) out of range...", op);
  return name;
}

bool is_op2(int op) {
  return strchr("+-*/%&|^<>", op) || (op > Op2Begin && op <Op2End);
}

void init() {
  memset(target, 0, sizeof(target));
}

int read_source(char *iFile) {
  FILE *fd;
  init();
  if (!(fd = fopen(iFile, "r"))) {
    printf("could not open(%s)\n", iFile);
    return -1;
  }
  int len = fread(source, 1, sizeof(source), fd);
  source[len++] = '\n'; source[len++] = '\0';
  printf("=====source=======\n%s\n==================\n", source);
  return 0;
}
