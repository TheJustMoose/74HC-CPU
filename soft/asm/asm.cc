/*

Ассемблер для моего 74HCPU под новую систему команд:

    4   +  3  +1+  3  +   5   = 16
 0 1 2 3 4 5 6 7 8 9 A B C D E F         флаги
-----------------------------------------------
|   ADD | DST |C| SRC |-|Z|z|I|i| 00 0000  *  // ADDI  R0, 1    // INC R0;
|  ADDC | DST |C| SRC |F|Z|z|I|i| 01 0001  *  // ADDCI R1, 0    // INCC R1;    // бит F нужен для команд -INC-, -DEC-, SUB, -INV-, NEG
|   AND | DST |C| SRC |-|Z|z|I|i| 02 0010  *  // ANDI R2, 0x0F  // здесь есть свободный бит, и вместо F туда можно положить S[WAP] или S[HIFT]
|    OR | DST |C| SRC |-|Z|z|I|i| 03 0011  *  // ORI R3, 2      // в любом случае, сдвиг старшего нибла на место младшего кажется полезным
|   XOR | DST |C| SRC |-|Z|z|I|i| 04 0100  *  // XORI R4, 4     // кстати, в этом случае можно ещё и от команды SWAP избавиться
|   MUL | DST |C| SRC |-|Z|z|I|i| 05 0101  *  // MULI R6, 10    // R7:R6 := R6*10
|   UNO | DST |0|TYP|-|F|-|-|-|-| 06 0110  *  // унарные команды не используют операнд SRC, поэтому нельзя использовать инверторы и отдельные нибблы
|   MOV | DST |C| SRC |*|Z|z|I|i| 07 0111  -  // MOVI R5, 5     // LDI R5, 5       // * - можно использовать, чтобы пихать адрес в SPL/SPH (правда, только из других регистров)
|   LPM | DST |W|EXT|?|U|OFFSET4| 08 1000  -  // LPM R0, [IX]   // LPM R1, [X+1]   // LPM R1, [DX-1]  // W - читать слово (1) или байт (0)
|    LD | DST |0|EXT|D|U|OFFSET4| 09 1001  -  // LD R1, [-Y]    // LD R3, [+SP-1] ; POP R3
|    IN | DST |  PORT   |-|-|I|i| 0A 1010  -  // IN R2, PIN1    // IN R2, ~PIN1 ; инвертировать порт перед чтением
|-------------|7-8-9-A-B|-------|------------ всё что ниже - не модифицирует регистры
|   OUT | SRC |  PORT   |O|o|X|x| 0B 1011  -  // OUT PORT0, R2  // XOUT PORT0, R2
|    ST | SRC |0|EXT|D|U|OFFSET4| 0C 1100  -  // ST [Y], R2     // ST [IX], R2     // ST [Y+2], R2   // ST [-SP], R2 ; PUSH R2
|   CMP | DST |C| SRC |-|   -   | 0D 1101  +  // CMPI R3, 10    // CMP  R0, R2
|  CMPC | DST |C| SRC |-|   -   | 0E 1110  +  // CMPCI R4, 10   // CMPC R1, R3
| BRNCH |  CALL | 8 bit OFFSET  | 0F 1111 0000 // переход в +-127 команды, значение прибавляется к текущему счётчику команд
| BRNCH |   JMP | 8 bit OFFSET  | 0F 1111 0001 <- COP low byte
| BRNCH |   RET | 8 bit +STACK  | 0F 1111 0010 // на сколько байт переместить указатель стека, дабы пропустить запушенные параметры
| BRNCH |    JZ | 8 bit OFFSET  | 0F 1111 0011 // условные переходы
| BRNCH |    JL | 8 bit OFFSET  | 0F 1111 0100
| BRNCH |   JNE | 8 bit OFFSET  | 0F 1111 0101
| BRNCH |    JE | 8 bit OFFSET  | 0F 1111 0110
| BRNCH |    JG | 8 bit OFFSET  | 0F 1111 0111
| BRNCH |    JC | 8 bit OFFSET  | 0F 1111 1000
| BRNCH |   JNZ | 8 bit OFFSET  | 0F 1111 1001
| BRNCH |   JNC | 8 bit OFFSET  | 0F 1111 1010
| BRNCH |   JHC | 8 bit OFFSET  | 0F 1111 1011
| BRNCH |  JNHC | 8 bit OFFSET  | 0F 1111 1100
| BRNCH |  STOP |   0000 0000   | 0F 1111 1101 // отладочный стоп, чтобы можно было смотреть глазами регистры (и есть 8 бит на фантазию, например останавливаться только при записи в порт)
| BRNCH |AFCALL | Hi 8 bit ADDR | 0F 1111 1110 // Absolute Far Call - 8 bit ADDR кладём в старшие биты и ничего не добавляем к младшим
| BRNCH |   NOP |   1111 1111   | 0F 1111 1111 // NOP - хорошо бы чтоб имел код 0xFF, это позволит думать, что не прошитая память заполнена NOP-ами
*/

#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

int process(string fname);

void help() {
  printf("74HCPU assembler v 0.2\n");
  printf("Support next instructions:\n");
  printf("arithmetic: ADD, ADDC, AND, OR, XOR, MUL, UNO, MOV\n");
  printf("memory: LPM, LD, ST\n");
  printf("port: IN, OUT\n");
  printf("compare: CMP, CMPC\n");
  printf("jmp: CALL, JMP, RET, JZ, JL, JNE, JE, JG, JC, JNZ, JNC, JHC, JNHC, STOP, AFCALL, NOP\n");
  printf("Registers: R0, R1, R2, R3, R4, R5, R6, R7\n");
  printf("Register pointers: X(XL+XH), Y(YL+YH), Z(ZL+ZH), SP(SPL+ZPH)\n");
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    help();
    return 0;
  }

  if (argc == 2 && argv[1]) {
    string cmd(argv[1]);
    if (cmd == "help") {
      help();
      return 0;
    }

    // okay, probably cmd is file name ;)
    return process(cmd);
  }

  printf("argc: %d\n", argc);
  return 0;
}

vector<string> lines;

int process(string fname) {
  FILE* f = fopen(fname.c_str(), "r");
  if (!f) {
    printf("Error. Can't open file %s\n", fname.c_str());
    return 1;
  }
  fclose(f);

  return 0;
}
