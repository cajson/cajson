# Cajson -- EBNF

```EBNF
stmts = stmt*

block = { stmts }

stmt = while expr stmt           | 
       if expr stmt (else stmt)? |
       for id (in|of) expr stmt  |
       for id=expr to expr step expr stmt |
       return expr               |
       continue                  |
       break                     |
       (id=)? expr

expr = item (op2 expr)*

item = Num | Str | function | array | block | ( expr ) | term

function = fn (params) block

params = param*

param = id (:expr)?

array = [ expr* ]

args  = ( expr* )

term =  id ( [expr] | . id | args )*

num : integer | float
str : '...'
id  : [a-zA-Z_][a-zA-Z_0-9]*
```
