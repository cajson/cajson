#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NMAX 100000
int src, debug, o_run, o_dump;
int line = 1;
// char data[NMAX], *datap=data;
char source[NMAX], *p=source, *lp=source;
char target[NMAX], *e=target, *le=target;

#define error(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define emit(...) { printf(__VA_ARGS__); sprintf(e, __VA_ARGS__); e+=strlen(e); }

// token 的 id 與 vm 的 op 共用列舉編碼
enum { // token : 0-127 直接用該字母表達， 128 以後用代號。
  None=0,
  Id, Num, Str, Fn, Sys, 
  If, Else, Return, While,
  Block, Stmts, 
  Op1, Inc, Dec, Op1End,  // 一元運算
  Op2, Lor, Land, Eq, Neq, Le, Ge, Shl, Shr, Op2End, // 二元運算 
  AsciiBegin=32,
  Or='|',And='&',Assign='=',Xor='^',Add='+',Sub='-',Mul='*',Div='/', Mod='%'
};

char *op_names[] = {
  "none", 
  "id", "num", "str", "fn", "sys", 
  "else", "if", "return", "while",
  "op1", "++", "--", "op1end",
  "op2", "||", "&&", "==", "!=", "<=", ">=", "<<", ">>", "op2end"
};

char* op_name(int op, char *name) {
  if (op > AsciiBegin)
    sprintf(name, "%c", (char) op);
  else if (op >= 0)
    sprintf(name, "%s", op_names[op]);
  else
    error("op_name(%d) out of range...", op);
  return name;
}

bool is_op2(char op) {
  return strchr("+-*/%&|^", op) || (op >= Op2 && op <=Op2End);
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
