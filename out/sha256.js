// source file: prog/sha256.cj
import '../sys/cj.js'
/* 0  */	import * as H from 'https://deno.land/std/hash/mod.ts';
/* 2  */	function hash(text)
/* 0  */	{
/* 3  */	  let h1=H.createHash('sha256');
/* 4  */	  h1.update(text);
/* 5  */	  return str(h1);
/* 0  */	};
/* 8  */	let record={nonce:0,data:'john => mary $2.7'};
/* 13 */	let json=JSON.stringify(record,null,2);
/* 14 */	print('json=',json);
/* 16 */	let digest=hash(json);
/* 17 */	print('digest=',digest);
