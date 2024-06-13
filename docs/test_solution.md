# 黑盒测试


- program -> block
- block -> { stmts }
- stmts -> stmt stmts | ε
- stmt -> id = expr ; 
    - | if ( bool ) stmt
    - | if ( bool) stmt else stmt
    - | while (bool) stmt 
    - | block
- bool -> expr < expr 
    - | expr <= expr 
    - | expr > expr 
    - | expr >= expr 
    - | expr
- expr -> expr + term 
    - | expr - term 
    - | term
- term -> term * factor
    - | term / factor 
    - | factor
- factor -> ( expr ) | ID | NUM

### 等价类划分

| 条件       | 文法                                 | 有效等价类                           | 无效等价类                                |
| ---------- | ------------------------------------ | ------------------------------------ | ----------------------------------------- |
| 程序       | `program -> block`                   | `{ stmts }`                          |                                           |
| 语句块     | `block -> { stmts }`                 | `{ stmts }`                          | 缺少 { } 的语句块                         |
| 语句       | `stmts -> stmt stmts`                | `stmt stmt`                          |                                           |
| 语句       | `stmts -> ε`                         | 空语句                               |                                           |
| 赋值语句   | `stmt -> id = expr ;`                | `id = expr ;`                        | 缺少分号的赋值语句， 赋值语句缺少表达式。 |
| if语句     | `stmt -> if ( bool ) stmt`           | `if ( expr < expr ) stmt`            | 缺少()的 if 语句， 缺少bool表达式的if语句 |
| ifelse语句 | `stmt -> if ( bool ) stmt else stmt` | `if ( expr <= expr ) stmt else stmt` | 缺少()的ifelse语句                        |
| while语句  | `stmt -> while ( bool ) stmt`        | `while ( expr > expr ) stmt`         | 缺少()的while语句                         |
| 语句块     | `stmt -> block`                      |                                      |                                           |
| 布尔表达式 | `bool -> expr < expr`                | `expr < expr`                        | 非法比较运算符                            |
|            | `bool -> expr <= expr`               | `expr <= expr`                       |                                           |
|            | `bool -> expr > expr`                | `expr > expr`                        |                                           |
|            | `bool -> expr >= expr`               | `expr >= expr`                       |                                           |
|            | `bool -> expr`                       | `expr`                               |                                           |
| 表达式     | `expr -> expr + term`                | `expr + term`                        | 非法运算符，运算符只有一个操作数          |
| 表达式     | `expr -> expr - term`                | `expr - term`                        |                                           |
| 表达式     | `expr -> term`                       | `term`                               |                                           |
| 项         | `term -> term * factor`              | `term * factor`                      |                                           |
| 项         | `term -> term / factor`              | `term / factor`                      |                                           |
| 项         | `term -> factor`                     | `factor`                             |                                           |
| 因子       | `factor -> ( expr )`                 | `( expr )`                           | 因子内没有表达式，因子缺少右括号          |
| 因子       | `factor -> ID`                       | `ID`                                 |                                           |
| 因子       | `factor -> NUM`                      | `NUM`                                |                                           |
