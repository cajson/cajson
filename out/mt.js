// source file: prog/mt.cj
import { print } from '../sys/cj.js'
/* 0  */	let e2c={dog:'狗',cat:'貓',a:'一隻',the:'這隻',chase:'追',bite:'吃'};
/* 2  */	let translate=function(ewords)
/* 0  */	{
/* 3  */	  let cwords=[];
/* 4  */	  for (let e of ewords)
/* 0  */	  {
/* 5  */	    cwords.push(e2c[e]);
/* 0  */	  };
/* 7  */	  return cwords;
/* 0  */	};
/* 10 */	let c=translate(['a','dog','chase','a','cat']);
/* 11 */	print(c);
