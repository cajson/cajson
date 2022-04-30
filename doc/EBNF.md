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

item = Num | Str | fn | array | block | ( expr ) | term

term =  Name ([expr] | . Name | args )*

array = [ expr* ]

args  = ( expr* )
```
