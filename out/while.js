// source file: prog/while.cj
import '../sys/cj.js'
/* 0  */	let sum=function (n)
/* 0  */	{
/* 1  */	  let i=1;
/* 2  */	  let s=0;
/* 3  */	  while (i<=n)
/* 0  */	  {
/* 4  */	    s=(s+i);
/* 5  */	    i=(i+1);
/* 0  */	  };
/* 7  */	  return s;
/* 0  */	};
/* 10 */	print('sum(10)=',sum(10));
