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

item = Num | Str | function | array | block | ( expr ) | term

function = fn (params) block

params = (id(=expr)?)*

array = [ expr* ]

args  = ( expr* )

term =  id ( [expr] | . id | args )*

num : integer | float
str : '...'
id  : Alphabet Sequence
```
