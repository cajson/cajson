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
