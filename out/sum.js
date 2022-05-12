// source file: prog/sum.cj
import '../sys/cj.js'
/* 1  */	let sum=function (n)
/*    */	{
/* 2  */	  let s=0;
/* 3  */	  for (let i=1;i<=n;i++) s=(s+i);;
/* 4  */	  return s;
/*    */	};
/* 7  */	print('sum(10)=',sum(10));
