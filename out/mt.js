// source file: prog/mt.cj
import '../sys/cj.js'
/* 1  */	let e2c={dog:'狗',cat:'貓',a:'一隻',the:'這隻',chase:'追',bite:'吃'};
/* 3  */	let translate=function (ewords)
/*    */	{
/* 4  */	  let cwords=[];
/* 5  */	  for (let e of ewords)
/*    */	  {
/* 6  */	    cwords.push(e2c[e]);
/*    */	  };
/* 8  */	  return cwords;
/*    */	};
/* 11 */	let c=translate(['a','dog','chase','a','cat']);
/* 12 */	print(c);
