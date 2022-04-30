# Cajson -- EBNF

```EBNF
stmts = stmt*

block = { stmts }

stmt = while expr block          | 
       if expr stmt (else stmt)? |
       for id in expr stmt       | 
       return exp                |
       (id=)? expr

expr = item (op2 expr)*

item = Number | String | function | array | block | ( expr ) | term

function = fn (params) block

array = [ expr* ]

args  = ( expr* )

term =  Name ( [expr] | . Name | args )*

Number : Integer | Float
String : '...'
Name   : Alphabet Sequence 
```
