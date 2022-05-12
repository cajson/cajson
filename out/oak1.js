// source file: prog/oak1.cj
import '../sys/cj.js'
/* 0  */	import * as oak from 'https://deno.land/x/oak/mod.ts';
/* 2  */	let app=new oak.Application();
/* 4  */	app.use(function (ctx)
/* 0  */	{
/* 5  */	  ctx.response.body='Hello World!';
/* 0  */	});
/* 8  */	print('start at : http://127.0.0.1:8000');
/* 9  */	await app.listen({port:8000});
