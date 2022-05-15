#include <stdio.h>

int tk = 1;
// #define skip(t) { int r=tk; if (tk==t) next(); else perror(); return r; }
#define skip(t) ({tk= 2;tk;})

int main() {
  int t = skip(3);
  printf("t=%d\n", t);
}
