// source file: prog/import.cj

/* 0  */	import 'https://deno.land/std/hash/mod.ts' as H;
/* 2  */	fn hash(text)
/* 0  */	{
/* 3  */	  h1:=H.createHash('sha256');
/* 4  */	  h1.update(text);
/* 5  */	  return str(h1);
/* 0  */	};
/* 8  */	print('hash(hello)=',hash('hello'));
