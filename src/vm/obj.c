#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// The Lisp object type
enum { // Regular objects visible from the user
    TNIL = 1,  // Nil
    TBOOL,     // 布林
    TFLOAT,    // 數值
    TSTRING,   // 字串
    TSYMBOL,   // 符號
    TPRIMITIVE,// 基本函數
    TFUNCTION, // 自訂函數
    TENV,      // 環境 frame
    TMOVED     // 垃圾蒐集時標示已經被移動過了
};

struct Obj;
typedef struct Obj *Primitive(void *root, struct Obj *env, struct Obj *arg);

typedef struct Function {
    struct Obj *params; // 巨集參數
    struct Obj *body;   // 巨集 body
    struct Obj *env;    // 巨集 env 環境變數
} Function;

typedef struct Env {
    struct Obj *vars;
    struct Obj *up;
} Env;

// The object type
typedef struct Obj {
    int type; // 物件型態
    int size; // 物件大小，算入 type 欄位
    union {   // Object values.
        bool bvalue;   // 布林
        double fvalue; // 浮點
        char *str;     // 字串
        char name[1];  // 變數名稱
        Primitive *pf; // 基本函數
        Function *f;   // 函數
        Env *env;      // 環境變數
        // void *moved;   // 移動後物件的新位址
    };
} Obj;

void *root = NULL;
void *env = NULL;

// Constants
Obj *True  = &(Obj){ .type=TBOOL,   .bvalue=true };
Obj *False = &(Obj){ .type=TBOOL,   .bvalue=false };
Obj *Zero  = &(Obj){ .type=TFLOAT,  .fvalue=0.0 };
Obj *Pi    = &(Obj){ .type=TFLOAT,  .fvalue=M_PI };
Obj *Empty = &(Obj){ .type=TSTRING, .str="" };
Obj *Nil   = &(Obj){ .type=TNIL };

// (print expr)
Obj *prim_print(void *root, Obj *env, Obj *obj) {
    // DEFINE1(tmp);
    switch (obj->type) {
        case TNIL: printf("nil"); break;
        case TBOOL: printf("%s", (obj->bvalue)?"true":"false"); break;
        case TFLOAT: printf("%f", obj->fvalue); break;
        case TSTRING: printf("%s", obj->str); break;
        case TSYMBOL: printf("symbol(%s)", obj->name); break;
        case TPRIMITIVE: printf("<primitive>"); break;
        case TFUNCTION: printf("<function>"); break;
    }
    return Nil;
}

Obj *prim_println(void *root, Obj *env, Obj *obj) {
    prim_print(root, env, obj);
    printf("\n");
}

Obj *Println = &(Obj){ .type=TPRIMITIVE, .pf=prim_print };

