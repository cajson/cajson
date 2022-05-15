// source file: prog/map.cj

/* 1  */	ccc:={name:'ccc',age:52};
/* 2  */	print(ccc);
/* 4  */	e2c:=map{dog:'狗',cat:'貓',a:'一隻',the:'這隻',chase:'追',bite:'吃'};
/* 5  */	print(e2c);
/* 7  */	Person:=class{__init:fn (name,age)
/*    */	{
/* 9  */	  $name=name;
/* 10 */	  $age=age;
/*    */	}};
/* 13 */	print(Person);
