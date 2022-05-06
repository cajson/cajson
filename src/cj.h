#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define error(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define size(x) (sizeof(x)/sizeof(typeof (x)))
// sym
typedef struct sym_t {
    char *name;
    int len;
} sym_t;

// lex
typedef enum id_t { // token : 0-127 直接用該字母表達， 128 以後用代號。
  None=0,
  Or='|',And='&', Xor='^',Add='+',Sub='-',Mul='*',Div='/', Mod='%',
  AsciiEnd=128, 
  Id, Num, Str, Function, Array, Map, Pair, Block, Args, Params, Param, 
  If, Return, While, ForIn, ForOf, ForTo, 
  Stmts, Stmt, Expr, Item, Term, Assign, Type,
  Op0Begin=200, Continue, Break, Op0End,
  Op1Begin, Neg, Inc, Dec, Op1End, 
  Op2Begin, Lor, Land, Eq, Neq, Le, Ge, Shl, Shr, Op2End,
  End,
} id_t;

typedef struct token_t {
    id_t type;   // token 型態
    int line;   // 所在行號
    char *str;  // token 的字串
    int len;    // token 的字串長度
    sym_t *sym; // 指向 symbol
} token_t;

// ast
typedef struct node_t node_t;
typedef struct array_t array_t;
typedef struct link_t link_t;
typedef struct list_t list_t;

struct node_t {
  int type;
  int line; // 該節點對應原始程式碼的行號
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

// API
int read_source(char *iFile);
void lex(char *source);
node_t *parse(char *source);
void gen_cj(node_t *root);
