/*
  Cmd system of 74hcpu:

|---------------------------------------------|f|
|   4   +  3 + 1 + 3  +    5    = 16          |l|
|   HIGH BYTE   |    LOW BYTE   |  HIGH BYTE  |a|
|0 1 2 3 4 5 6 7 8 9 A B C D E F|   (again)   |g|
|---------------------------------------------|s|
|   ADD | DST |C| SRC |-|Z|z|I|i| 00 0000 0000|*|
|  ADDC | DST |C| SRC |F|Z|z|I|i| 10 0001 0000|*|
|   AND | DST |C| SRC |-|Z|z|I|i| 20 0010 0000|*|
|    OR | DST |C| SRC |-|Z|z|I|i| 30 0011 0000|*|
|   XOR | DST |C| SRC |-|Z|z|I|i| 40 0100 0000|*|
|   MUL | DST |C| SRC |-|Z|z|I|i| 50 0101 0000|*|
|   UNO | DST |0|-|TYP|F|-|-|-|-| 60 0110 0000|*|
|   MOV | DST |C| SRC |*|Z|z|I|i| 70 0111 0000| |
|   LPM | DST |W|EXT|D|U|OFFSET4| 80 1000 0000| |
|    LD | DST |0|EXT|D|U|OFFSET4| 90 1001 0000| |
|    IN | DST |  PORT   |-|-|I|i| A0 1010 0000| |
|-------------|7-8-9-A-B|-------|-------------|-|
|   OUT | SRC |  PORT   |O|o|X|x| B0 1011 0000| |
|    ST | SRC |0|EXT|D|U|OFFSET4| C0 1100 0000| |
|   CMP | DST |C| SRC |-|   -   | D0 1101 0000|+|
|  CMPC | DST |C| SRC |-|   -   | E0 1110 0000|+|
| BRNCH |  CALL | 8 bit OFFSET  | F0 1111 0000| |
| BRNCH |   JMP | 8 bit OFFSET  | F1 1111 0001| |
| BRNCH |   RET | 8 bit +STACK  | F2 1111 0010| |
| BRNCH |    JZ | 8 bit OFFSET  | F3 1111 0011| |
| BRNCH |    JL | 8 bit OFFSET  | F4 1111 0100| |
| BRNCH |   JNE | 8 bit OFFSET  | F5 1111 0101| |
| BRNCH |    JE | 8 bit OFFSET  | F6 1111 0110| |
| BRNCH |    JG | 8 bit OFFSET  | F7 1111 0111| |
| BRNCH |    JC | 8 bit OFFSET  | F8 1111 1000| |
| BRNCH |   JNZ | 8 bit OFFSET  | F9 1111 1001| |
| BRNCH |   JNC | 8 bit OFFSET  | FA 1111 1010| |
| BRNCH |   JHC | 8 bit OFFSET  | FB 1111 1011| |
| BRNCH |  JNHC | 8 bit OFFSET  | FC 1111 1100| |
| BRNCH |  STOP |   0000 0000   | FD 1111 1101| |
| BRNCH |AFCALL | Hi 8 bit ADDR | FE 1111 1110| |
| BRNCH |   NOP |   1111 1111   | FF 1111 1111| |
|---------------------------------------------|-|

*/

#include "emul.h"

