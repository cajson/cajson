// source file: prog/for.cj
import { print } from '../sys/cj.js'
/* 0  */	let a=[5,4,3,2,1];
/* 2  */	for (let i in a) print(a[i]);;
/* 4  */	for (let o of a) print(o);;
/* 6  */	for (let i=1;i<=10;i+=2) print(i);;
/* 8  */	for (let i=1;i<=10;i++)
/* 0  */	{
/* 9  */	  if (i==2) continue;;
/* 10 */	  print(i);
/* 11 */	  if (i==5) break;;
/* 0  */	};
