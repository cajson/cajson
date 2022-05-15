// source file: prog/map.cj
import '../sys/cj.js'
/* 1  */	let ccc={name:'ccc',age:52};
/* 2  */	print(ccc);
/* 4  */	let e2c={dog:'狗',cat:'貓',a:'一隻',the:'這隻',chase:'追',bite:'吃'};
/* 5  */	print(e2c);
/* 7  */	let Person=class {
/* 8  */	constructor(name,age)
/*    */	{
/* 9  */	  this.name=name;
/* 10 */	  this.age=age;
/*    */	}
/* 12 */	__str()
/*    */	{
/* 13 */	  return (this.name+(' '+this.age));
/*    */	}
};
/* 16 */	print(Person);
/* 18 */	let p=new Person('ccc',52);
/* 19 */	print(str(p));
/* 20 */	print(p);
