// source file: prog/try.cj
import '../sys/cj.js'
/* 1  */	try 
/*    */	{
/* 2  */	  throw Error('Error');
/*    */	} catch (error)
/*    */	{
/* 4  */	  print(error);
/*    */	};
