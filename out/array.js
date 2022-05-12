// source file: prog/array.cj
import '../sys/cj.js'
/* 1  */	function mean(a)
/*    */	{
/* 2  */	  let s=0;
/* 3  */	  for (let i in a) s=(s+a[i]);;
/* 4  */	  return (s/a.length);
/*    */	};
/* 7  */	print('mean([1 2 3 4 5])=',mean([1,2,3,4,5]));
