#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NMAX 100000
#define error(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define size(x) (sizeof(x)/sizeof(typeof (x)))

// lex
typedef enum id_t { // token : 0-127 直接用該字母表達， 128 以後用代號。
  None=0,
  Or='|',And='&', Xor='^',Add='+',Sub='-',Mul='*',Div='/', Mod='%',
  AsciiEnd=128, 
  Id, Num, Str, Function, Array, Map, Pair, Block, Args, Params, Param, 
  If, While, ForIn, ForOf, ForTo, 
  Stmts, Stmt, Expr, Item, Term, Assign, Type,
  Op0Begin=200, Continue, Break, Op0End,
  Op1Begin, Neg, Inc, Dec, Return, Op1End, 
  Op2Begin, Lor, Land, Eq, Neq, Le, Ge, Shl, Shr, Op2End,
  End,
} id_t;

typedef struct token_t {
    int type;   // token 型態
    int line;   // 所在行號
    char *str;  // token 的字串
    int len;    // token 的字串長度
    // sym_t *sym; // 指向 symbol
} token_t;

// ast
typedef struct node_t node_t;
typedef struct array_t array_t;
typedef struct link_t link_t;
typedef struct list_t list_t;

struct node_t {
  int type;
  int len;
  token_t *ptk;
  union {
    list_t  *list;
    node_t  *node;
    node_t  **array;
  };
};

struct link_t {
  node_t *node;
  link_t *next;
};

struct list_t {
  int len;
  link_t *head;
};

// API
int read_source(char *iFile);
void lex(char *source);
node_t *parse(char *source);
void gen_cj(node_t *root);
