// source file: prog/class.cj
import '../sys/cj.js'
/* 1  */	let Person=class {
/* 2  */	constructor(name,age)
/*    */	{
/* 3  */	  this.name=name;
/* 4  */	  this.age=age;
/*    */	}
/* 6  */	__str()
/*    */	{
/* 7  */	  return (this.name+(' '+this.age));
/*    */	}
};
/* 10 */	print(Person);
/* 12 */	let p=new Person('ccc',52);
/* 13 */	print(str(p));
/* 14 */	print(p);
