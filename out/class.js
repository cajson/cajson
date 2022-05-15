// source file: prog/class.cj
import '../sys/cj.js'
/* 1  */	class Person {
/* 2  */	  constructor(name,age)
/*    */	  {
/* 3  */	    this.name=name;
/* 4  */	    this.age=age;
/*    */	  }
/* 6  */	  __str()
/*    */	  {
/* 7  */	    return (this.name+(' '+this.age));
/*    */	  }
/*    */	};
/* 11 */	print(Person);
/* 13 */	let p=new Person('ccc',52);
/* 14 */	print(str(p));
/* 15 */	print(p);
