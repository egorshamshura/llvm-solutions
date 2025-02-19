# llvm-course task 4 solution
## my ISA specification
| Command                | Description   | Operation                    |
| ---------------------- | ------------- | ---------------------------- |
| ADD  x1 x2 x3          | 3 regs        | x1 = x2 + x3                 |
| ADDi x1 x2 imm3        | 2 regs, 1 imm | x1 = x2 + imm3               |
| SUB  x1 x2 x3          | 3 regs        | x1 = x2 - x3                 |
| SUBi x1 x2 imm3        | 2 regs, 1 imm | x1 = x2 - imm3               |
| MUL  x1 x2 x3          | 3 regs        | x1 = x2 * x3                 |
| DIV  x1 x2 x3          | 3 regs        | x1 = x2 / x3                 |
| REM  x1 x2 x3          | 3 regs        | x1 = x2 % x3                 |
| AND  x1 x2 x3          | 3 regs        | x1 = x2 & x3                 |
| ANDi x1 x2 imm3        | 2 regs, 1 imm | x1 = x2 & imm3               |
| XOR  x1 x2 x3          | 3 regs        | x1 = x2 ^ x3                 |   
| EQi  x1 x2 x3          | 2 regs, 1 imm | x1 = (x2 == imm3)            |
| INC_NEi x1 x2 imm3     | 2 regs, 1 imm | x1 = (++x2 != imm3)          |
| PUT_PIXEL x1 x2 x3     | 3 regs        | simPutPixel(x1, x2, x3)      | 
| ALLOC x1 imm2          | 1 reg,  1 imm | x1 = alloc(imm2)             | 
| WRITE64 x1 x2 x3       | 3 regs        | *(x1 + x2) = x3 in 64bit     | 
| WRITE64ii x1 imm2 imm3 | 1 reg,  2 imm | *(x1 + imm2) = imm3 in 64bit | 
| WRITE64ri x1 x2 imm3   | 2 regs, 1 imm | *(x1 + x2) = imm3 in 64bit   |
| READ64 x1 x2 x3        | 3 regs        | x1 = *(x2 + x3) in 64bit     |  
| RAND64 x1              | 1 reg         | x1 = rand()                  | 
| DUMP x1                | 1 reg         | writes in console x1         | 
| FLUSH x1               |               | simFlush()                   | 




