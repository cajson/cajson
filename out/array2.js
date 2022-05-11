// source file: prog/array2.cj
import '../sys/cj.js'
/* 0  */	function mean(a,len)
/* 0  */	{
/* 1  */	  let s=0;
/* 2  */	  for (let i=0;i<=(len-1);i++) s=(s+a[i]);;
/* 3  */	  return (s/len);
/* 0  */	};
/* 6  */	print('mean([1 2 3 4 5])=',mean([1,2,3,4,5],5));
