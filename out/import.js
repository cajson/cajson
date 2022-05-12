// source file: prog/import.cj
import '../sys/cj.js'
/* 1  */	import * as H from 'https://deno.land/std/hash/mod.ts';
/* 3  */	function hash(text)
/*    */	{
/* 4  */	  let h1=H.createHash('sha256');
/* 5  */	  h1.update(text);
/* 6  */	  return str(h1);
/*    */	};
/* 9  */	print('hash(hello)=',hash('hello'));
