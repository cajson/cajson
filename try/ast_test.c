#include <init.c>
#include <sym.c>
#include <lex.c>
#include <ast.c>
#include <parse.c>
#include <gen_js.c>

int main(int argc, char **argv) {
    node_t n[] = {{ .type=1,}, {.type=2}, {.type=3}};
    link_t ln[] = { 
        {.node=n[0], .next=ln[1]}, 
        {.node=n[1], .next=ln[2]}, 
        {.node=n[2], .next=NULL}, 
    };
    list_t *t = {.head=ln[0]}
    list_reverse(t);
}
