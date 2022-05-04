#include <cj.h>
#include <init.c>
#include <sym.c>
#include <lex.c>
#include <ast.c>
#include <parse.c>
#include <gen_cj.c>

int main(int argc, char **argv) {
  char *narg;
  int o_save = 0, o_lex = 0;
  // 主程式
  --argc; ++argv; // 略過執行檔名稱
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'l') { o_lex = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 's') { src = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'd') { debug = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'r') { o_run = 1; --argc; ++argv; }
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'u') { o_dump = 1; --argc; ++argv; }
  if (argc < 1) { printf("usage: cj [-s] [-d] [-r] [-u] in_file [-o] out_file...\n"); return -1; }
  iFile = *argv;
  if (argc > 1) {
    narg = *(argv+1);
    if (*narg == '-' && narg[1] == 'o') {
      o_save = 1;
      oFile = *(argv+2);
    }
  }
  read_source(iFile);
  if (o_lex) { lex(source); return 1; }
  node_t *ast = parse(source);
  gen_cj(ast);
  printf("\n");
}
