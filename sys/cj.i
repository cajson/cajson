# 1 "cj.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "cj.c"
# 17 "cj.c"
typedef struct Str {
    char *str;
    int length;
} Str;

typedef struct Array {
    int len;
    union {
        char *chara;
        int *inta;
        i8 *i8a;
        u8 *u8a;
        i32 *i32a;
        i64 *i64a;
        f64 *f64a;
    };
} Array;






typedef struct Obj {
} Obj;

int main() {

    Array x = { .length=10, .inta=(int[length]){} };;
    int t = x.inta[3];
    printf("t=%d\n", t);
}
