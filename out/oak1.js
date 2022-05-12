// source file: prog/oak1.cj
import '../sys/cj.js'
/* 1  */	import * as oak from 'https://deno.land/x/oak/mod.ts';
/* 3  */	let app=new oak.Application();
/* 5  */	app.use(function (ctx)
/* 0  */	{
/* 6  */	  ctx.response.body='Hello World!';
/* 0  */	});
/* 9  */	print('start at : http://127.0.0.1:8000');
/* 10 */	await app.listen({port:8000});
