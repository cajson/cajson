#include <obj.c>

int main() {
    prim_println(root, env, Nil);
    prim_println(root, env, True);
    prim_println(root, env, False);
    prim_println(root, env, Pi);
    Obj *s = &(Obj){ .type=TSTRING,.str="Hello!" };
    prim_println(root, env, s);
    prim_println(root, env, Println);
}
