// source file: prog/sum.cj
import '../sys/cj.js'
/* 0  */	let sum=function (n)
/* 0  */	{
/* 1  */	  let s=0;
/* 2  */	  for (let i=1;i<=n;i++) s=(s+i);;
/* 3  */	  return s;
/* 0  */	};
/* 6  */	print('sum(10)=',sum(10));
