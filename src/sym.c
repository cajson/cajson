typedef struct sym_t {
    char *name;
    int len;
    Obj *obj;
} sym_t;

#define NSYM 9997
sym_t symtb[NSYM];

int hash(char *name, int len) { // 計算雜湊值
    char *p = name;
    int h=1;
    while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_')
        h = h * 147 + *p++;
    h = (h << 6) + len;
    return h;
}

int sym_init() {
    memset(symtb, 0, sizeof(symtb));
}

sym_t *sym_find(char *name, int len, bool *found) {
    int si = hash(name, len)%NSYM, i=si;
    while (1) {
        sym_t *sym = &symtb[i];
        if (!sym->name) { *found=false; return sym; }
        if (len == sym->len && memcmp(sym->name, name, len)==0) { 
            *found=true; return sym;
        }
        if (++i == si) { *found=false; return NULL; }
    }
}

sym_t *sym_get(char *name, int len) {
    bool found;
    sym_t *sym = sym_find(name, len, &found);
    return sym;
}

sym_t *sym_add(char *name, int len) {
    bool found;
    sym_t *sym = sym_find(name, len, &found);
    if (!found) { sym->name=name; sym->len = len; }
    return sym;
}
