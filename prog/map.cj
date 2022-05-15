ccc := {name:'ccc', age:52}
print(ccc)

e2c:=map {dog:'狗', cat:'貓', a:'一隻', the:'這隻', chase:'追', bite:'吃'}
print(e2c)

Person := class {
    __init:fn(name, age) {
        $name = name
        $age = age
    },
    __str:fn() {
        return $name+' '+$age
    }
}
print(Person)

p:=new Person('ccc', 52)
print(str(p))
print(p)
