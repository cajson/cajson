// source file: prog/if.cj
import { print } from '../sys/cj.js'
/* 0  */	let max=function(x,y)
/* 0  */	{
/* 0  */	  if (x>y) return x; else return y;;
/* 0  */	};
/* 2  */	print('max(3 5)=',max(3,5));
