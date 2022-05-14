# gen_c.md

目前產生的 carray.c 有錯

```cpp
// source file: prog/c/carray.cj
#include <cj.h>

/* 1  */	int mean(int* a,int len)
/*    */	{
/* 2  */	  int s=0;
/* 3  */	  for (int i=0;i<=(len-1);i+=1) s=(s+a[i]);;
/* 4  */	  return (s/len);
/*    */	};
/* 7  */	int main()
/*    */	{
/* 8  */	  int* a={1,2,3,4,5};
/* 9  */	  printf("mean([1 2 3 4 5])=%d\n",mean(a,5));
/*    */	};
```

其中的 8 這個行，應該改成

```cpp
int* a=(int[]){1,2,3,4,5};
```

這意味著， cj 必須能將型態標上去。

問題是，自動標型態可行嗎？能做到甚麼程度呢？

```cpp
// source file: prog/c/carray.cj
#include <cj.h>

/* 1  */	int mean(int* a,int len)
/*    */	{
/* 2  */	  int s=0;
/* 3  */	  for (int i=0;i<=(len-1);i+=1) s=(s+a[i]);;
/* 4  */	  return (s/len);
/*    */	};
/* 7  */	int main()
/*    */	{
/* 8  */	  int* a=(int[]){1,2,3,4,5};
/* 9  */	  printf("mean([1 2 3 4 5])=%d\n",mean(a,5));
/*    */	};
```
