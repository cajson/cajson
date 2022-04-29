#include <init.c>
#include <obj.c>
#include <sym.c>
#include <lex.c>
#include <ast.c>
#include <parser.c>
#include <gen_js.c>

int main(int argc, char **argv) {
    read_source(argv[1]);
    src = true;
    node_t *prog=parse(source);
    gen_code(prog);
}
