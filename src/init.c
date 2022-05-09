char *ifile=NULL, *ofile=NULL;
int src, debug, o_run, o_dump;
char *source;

char *id_names[] = {
  "op0begin", "continue", "break", "op0end",
  "op1begin", "-", "++", "--", "return", "op1end",
  "op2begin", "||", "&&", "==", "!=", "<=", ">=", "<<", ">>", "op2end"
};

char* id_name(int op, char *name) {
  if (op < AsciiEnd)
    sprintf(name, "%c", (char) op);
  else if (op > Op0Begin && op < Op2End)
    sprintf(name, "%s", id_names[op-Op0Begin]);
  else
    error("id_name(%d) out of range...", op);
  return name;
}

bool is_op1(int op) {
  return contain("!~@$", op) || (op > Op1Begin && op <Op1End);
}

bool is_op2(int op) {
  return contain("+-*/%&|^<>", op) || (op > Op2Begin && op <Op2End);
}

int read_source(char *file) {
  FILE *fd;
  if (!(fd = fopen(file, "r"))) {
    printf("could not open(%s)\n", file);
    return -1;
  }
  int len = fread(source, 1, sizeof(source), fd);
  source[len++] = '\n'; source[len++] = '\0';
  // printf("=====source=======\n%s\n==================\n", source);
  return 0;
}
