#include <init.c>
#include <sym.c>
#include <lex.c>
#include <ast.c>
#include <parse.c>
// #include <gen_js.c>

int main(int argc, char **argv) {
    read_source(argv[1]);
    src = true;
    node_t *ast=parse(source);
    // gen_code(ast);
}
