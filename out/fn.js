// source file: prog/fn.cj
import '../sys/cj.js'
/* 1  */	let inc=function (x)
/*    */	{
/* 1  */	  return (x+1);
/*    */	};
/* 3  */	let add=function (x,y)
/*    */	{
/* 3  */	  return (x+y);
/*    */	};
/* 5  */	print('inc(2)=',inc(2));
/* 6  */	print('add(2,3)=',add(2,3));
