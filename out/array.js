// source file: prog/array.cj
import '../sys/cj.js'
/* 0  */	let mean=function(a)
/* 0  */	{
/* 1  */	  let s=0;
/* 2  */	  for (let i in a) s=(s+a[i]);;
/* 3  */	  return (s/a.length);
/* 0  */	};
/* 6  */	print('mean([1 2 3 4 5])=',mean([1,2,3,4,5]));
