// source file: prog/sha256.cj
import '../sys/cj.js'
/* 1  */	import * as H from 'https://deno.land/std/hash/mod.ts';
/* 3  */	function hash(text)
/*    */	{
/* 4  */	  let h1=H.createHash('sha256');
/* 5  */	  h1.update(text);
/* 6  */	  return str(h1);
/*    */	};
/* 9  */	let record={nonce:0,data:'john => mary $2.7'};
/* 14 */	let json=JSON.stringify(record,null,2);
/* 15 */	print('json=',json);
/* 17 */	let digest=hash(json);
/* 18 */	print('digest=',digest);
