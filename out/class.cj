// source file: prog/class.cj

/* 1  */	class Person{{__init:fn (name,age)
/*    */	{
/* 3  */	  $name=name;
/* 4  */	  $age=age;
/*    */	},__str:fn ()
/*    */	{
/* 7  */	  return ($name+(' '+$age));
/*    */	}}};
/* 11 */	print(Person);
/* 13 */	p:=new Person('ccc',52);
/* 14 */	print(str(p));
/* 15 */	print(p);
