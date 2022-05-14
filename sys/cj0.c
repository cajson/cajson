/*
#include <stdint.h>
*/
#include <stdio.h>

#define i8 char
#define i16 short
#define i32 long
#define i64 long long
#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define u64 unsigned long long
#define f32 float
#define f64 double

typedef struct Str {
    char *str;
    int len;
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

#define array(type, length) { .len=length, .type##a=(type[length]){} }
#define array1(type, length, init) { .len=length, .type##a=(type[length])init }
// https://gcc.gnu.org/onlinedocs/gcc-4.3.6/cpp/Concatenation.html#Concatenation
#define get(a, i) a.inta[i]
#define set(a, i, t) a.inta[i]=t

typedef struct Obj {
} Obj;

/*

int main() {
    Array x = { .len=10, .inta=(int[10]){0,1,2,3,4,5} };
    // int a[] = {0,1,2,3,4};
    // Array x = array(int, 10);
    // Array x = array1(int, 10, (int[10]){0,1,2,3,4,5});
    // x.inta = a;
    int t = get(x, 3);
    printf("t=%d\n", t); 
}
*/