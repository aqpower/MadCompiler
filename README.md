# MadCompiler

## Overview
MadCompiler is a compiler course design project from the NCHU computer science department.

## Features
- **Lexical Analysis:** Tokenizes the input source code.
- **Syntax Analysis:** Builds an Abstract Syntax Tree (AST).
- **Semantic Analysis:** Checks for semantic errors.
- **Code Generation:** Produces intermediate code.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/aqpower/MadCompiler.git
   ```
2. Build the project using CMake:
   ```bash
   cd MadCompiler
   mkdir build
   cmake -S . -B build
   cmake --build build
   ```

## Usage
Run the compiler with the following command:
```bash
./build/src/madcompiler <source_code_file> -o <output_file>
```

Generate the lexical analysis output:
```
./build/src/madcompiler <source_code_file> -l <output_file>
```

## Recognized Tokens
1. **Keywords:** `if`, `if else`, `while`; token type 1.
2. **Identifiers:** token type 2.
3. **Constants:** Unsigned integers; token type 3.
4. **Operators:** `+`, `-`, `*`, `/`, `=`, `>`, `<`, `<=`, `!=`; token type 4.
5. **Separators:** `,`, `;`, `{`, `}`, `(`, `)`; token type 5.
6. **Other Tokens:** Defined by the following regular expressions:
   - `ID = letter(letter | digit)*`
   - `NUM = digit digit*`

## Grammar Rules
The start symbol of the grammar is `program`. The following production rules are implemented:
- `program -> block`
- `block -> { stmts }`
- `stmts -> stmt stmts | ε`
- `stmt -> id = expr ;`
  - `| if ( bool ) stmt`
  - `| if ( bool) stmt else stmt`
  - `| while (bool) stmt`
  - `| block`
- `bool -> expr < expr`
  - `| expr <= expr`
  - `| expr > expr`
  - `| expr >= expr`
  - `| expr`
- `expr -> expr + term`
  - `| expr - term`
  - `| term`
- `term -> term * factor`
  - `| term / factor`
  - `| factor`
- `factor -> ( expr ) | ID | NUM`

## License
MIT License
