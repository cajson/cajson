// source file: prog/c/csum.cj
#include <cj.h>

/* 1  */	int sum(int n)
/*    */	{
/* 2  */	  int s=0;
/* 3  */	  for (int i=1;i<=n;i+=1) s=(s+i);;
/* 4  */	  return s;
/*    */	};
/* 7  */	int main()
/*    */	{
/* 8  */	  printf("sum(10)=%d\n",sum(10));
/*    */	};
