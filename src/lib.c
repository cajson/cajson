#include <stdio.h>

// =================== memory management: pool ================
#define NPTR 100000
void *pools[NPTR];
int poolTop = 0;

void *pool(int size) {
  void *p=malloc(size);
  memset(p, 0, size);
  if (!p) error("pool() alloc fail!");
  pools[poolTop++] = p;
  return p;
}

// =================== file system ================
int file_size(FILE *fp) {
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return sz;
}

char *file_read(char *fname) {
    FILE *fp = fopen(fname, "r");
    int sz = file_size(fp);
    char *buf = pool(sz+1);
    int len = fread(buf, 1, sz, fp);
    buf[len] = '\0';
    fclose(fp);
    return buf;
}
