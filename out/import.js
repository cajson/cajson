// source file: prog/import.cj
import '../sys/cj.js'
/* 0  */	import * as H from 'https://deno.land/std/hash/mod.ts';
/* 2  */	function hash(text)
/* 0  */	{
/* 3  */	  let h1=H.createHash('sha256');
/* 4  */	  h1.update(text);
/* 5  */	  return str(h1);
/* 0  */	};
/* 8  */	print('hash(hello)=',hash('hello'));
