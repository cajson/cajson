// source file: prog/while.cj
import '../sys/cj.js'
/* 1  */	let sum=function (n)
/*    */	{
/* 2  */	  let i=1;
/* 3  */	  let s=0;
/* 4  */	  while (i<=n)
/*    */	  {
/* 5  */	    s=(s+i);
/* 6  */	    i=(i+1);
/*    */	  };
/* 8  */	  return s;
/*    */	};
/* 11 */	print('sum(10)=',sum(10));
