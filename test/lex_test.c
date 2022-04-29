#include <init.c>
#include <obj.c>
#include <sym.c>
#include <lex.c>

int main(int argc, char **argv) {
    read_source(argv[1]);
    lex(source);
}

