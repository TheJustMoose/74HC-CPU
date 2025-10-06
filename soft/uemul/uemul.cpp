/*
|---------------------------------------------|f|
|   4   +  3 + 1 + 3  +    5    = 16          |l|
|   HIGH BYTE   |    LOW BYTE   |  HIGH BYTE  |a| * - меняем CF, HCF, ZF (результат сложения) == A-FLAGS (Arithm)
|0 1 2 3 4 5 6 7 8 9 A B C D E F|   (again)   |g| + - меняем LF, EQ, GF (результат сравнения) == C-FLAGS (Compare)
|---------------------------------------------|s|
|   ADD | DST |C| SRC |-|Z|z|I|i| 00 0000 0000|*| ADDI  R0, 1    // INC R0;
|  ADDC | DST |C| SRC |F|Z|z|I|i| 10 0001 0000|*| ADDCI R1, 0    // INCC R1;    // бит F нужен для команд -INC-, -DEC-, SUB, -INV-, NEG
|   AND | DST |C| SRC |-|Z|z|I|i| 20 0010 0000|*| ANDI R2, 0x0F  // здесь есть свободный бит, и вместо F туда можно положить S[WAP] или S[HIFT]
|    OR | DST |C| SRC |-|Z|z|I|i| 30 0011 0000|*| ORI R3, 2      // в любом случае, сдвиг старшего нибла на место младшего кажется полезным
|   XOR | DST |C| SRC |-|Z|z|I|i| 40 0100 0000|*| XORI R4, 4     // кстати, в этом случае можно ещё и от команды SWAP избавиться
|   MUL | DST |C| SRC |-|Z|z|I|i| 50 0101 0000|*| MULI R6, 10    // R7:R6 := R6*10
|   UNO | DST |0|-|TYP|F|-|-|-|-| 60 0110 0000|*| унарные команды не используют операнд SRC, поэтому нельзя использовать инверторы и отдельные нибблы
|   MOV | DST |C| SRC |*|Z|z|I|i| 70 0111 0000| | MOVI R5, 5     // LDI R5, 5       // * - можно использовать, чтобы пихать адрес в SPL/SPH (правда, только из других регистров), или для того, чтобы сделать MOVW
|   LPM | DST |W|EXT|D|U|OFFSET4| 80 1000 0000| | LPM R0, [IX]   // LPM R1, [X+1]   // LPM R1, [DX-1]  // W - читать слово (1) или байт (0)
|    LD | DST |0|EXT|D|U|OFFSET4| 90 1001 0000| | LD R1, [-Y]    // LD R3, [+SP-1] ; POP R3  // ноль на месте бита C можно использовать как пятый бит OFFSET-а
|    IN | DST |  PORT   |-|-|I|i| A0 1010 0000| | IN R2, PIN1    // IN R2, ~PIN1 ; инвертировать порт перед чтением
|-------------|7-8-9-A-B|-------|-------------|-| всё что ниже - не модифицирует регистры
|   OUT | SRC |  PORT   |O|o|X|x| B0 1011 0000| | OUT PORT0, R2  // XOUT PORT0, R2 (вместо Oo можно сделать вчетверо больше регистров!)
|    ST | SRC |0|EXT|D|U|OFFSET4| C0 1100 0000| | ST [Y], R2     // ST [IX], R2     // ST [Y+2], R2   // ST [-SP], R2 ; PUSH R2
|   CMP | DST |C| SRC |-|   -   | D0 1101 0000|+| CMPI R3, 10    // CMP  R0, R2
|  CMPC | DST |C| SRC |-|   -   | E0 1110 0000|+| CMPCI R4, 10   // CMPC R1, R3
| BRNCH |  CALL | 8 bit OFFSET  | F0 1111 0000| | переход в +-127 команды, значение прибавляется к текущему счётчику команд
| BRNCH |   JMP | 8 bit OFFSET  | F1 1111 0001| | <- COP low nibble
| BRNCH |   RET | 8 bit +STACK  | F2 1111 0010| | на сколько байт переместить указатель стека данных, дабы пропустить запушенные параметры
| BRNCH |    JZ | 8 bit OFFSET  | F3 1111 0011| | if (v == 0)    // UPD: всё равно у меня нет механизма для переставления SP на несколько байт за команду RET
| BRNCH |    JL | 8 bit OFFSET  | F4 1111 0100| | if (v < w)     // поэтому вместо константы можно воткнуть сюда битик указания на RETI, вместо RET
| BRNCH |    JE | 8 bit OFFSET  | F5 1111 0101| | if (v == w)    // а не правильней ли будет сделать JLE вдобавок к отдельным JL + JE ?
| BRNCH |   JNE | 8 bit OFFSET  | F6 1111 0110| | if (v != w)
| BRNCH | reser | 8 bit OFFSET  | F7 1111 0111| | RETI ?
| BRNCH |   JNZ | 8 bit OFFSET  | F8 1111 1000| | if (v != 0)
| BRNCH |    JC | 8 bit OFFSET  | F9 1111 1001| | if (CF == 1)
| BRNCH |   JNC | 8 bit OFFSET  | FA 1111 1010| | if (CF == 0)   // выкинуть инструкции, что реально не будут использоваться
| BRNCH |   JHC | 8 bit OFFSET  | FB 1111 1011| | if (HCF == 1)  // вкрутить что-то вроде NJMP offset (и делать реальный переход на offset*16, к примеру)
| BRNCH |  JNHC | 8 bit OFFSET  | FC 1111 1100| | if (HCF == 0)
| BRNCH |  STOP |   0000 0000   | FD 1111 1101| | отладочный стоп, чтобы можно было смотреть глазами регистры (и есть 8 бит на фантазию)
| BRNCH |AFCALL | Hi 8 bit ADDR | FE 1111 1110| | Absolute Far Call - 8 bit ADDR кладём в старшие биты и --ничего не добавляем к-- зануляем младшим
| BRNCH |   NOP |   1111 1111   | FF 1111 1111| | NOP - хорошо бы чтоб имел код 0xFF, это позволит думать, что не прошитая память заполнена NOP-ами
|---------------------------------------------|-|
      0     1    2    3    4     5    6    7
   | HCF | CF | ZF | LF | ~EQ | GF | BF | DBG | - чтение (DBG наверное стоит унести в отдельный регистр)
*/

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <stack>

using namespace std;

enum FLAGS {
  HCF = 0, CF = 1, ZF = 2, LF = 3, EF = 4, GF = 5, BF = 6, DBG = 7, FLAGS_CNT = 8
};

uint16_t cmds[256] = {
  0xFF00,
  0xFF00,
  0xFF00,
  0xFD00
};

uint8_t RAM[65536];

uint8_t PORTS[32];
uint8_t PINS[32];

uint8_t regs0[8];  // bank 0 of registers
uint8_t regs1[8];  // bank 1 of registers
uint8_t *regs = regs0;  // current bank of registers

bool flags[FLAGS_CNT];  // CPU flags

stack<uint16_t> stck;

bool stop = false;

uint16_t GetX() {
  uint16_t res = regs1[1];
  res <<= 8;
  res += regs1[0];
  return res;
}

void step(uint16_t cmd, uint16_t &ip) {
  uint8_t op = (cmd >> 8) & 0xFF;
  if (cmd & 0xF000)  // branches
    ;
  else  // arithm instructions
    op &= 0xF0;  // have to clean low bits

  cout << "IP: " << hex << ip
       << ", cmd: " << cmd
       << ", op: " << (uint16_t)op << endl;

  if (op >= 0x00 && op <= 0xE0) {
    uint8_t dst = (cmd >> 9) & 0x07;
    uint8_t rdst = regs[dst];
    uint8_t cnst = (cmd >> 8) & 0x01;
    uint8_t src = (cmd >> 5) & 0x07;
    uint8_t rsrc = cnst ? (cmd & 0xFF) : regs[src];
    switch (op) {
      case 0x00: flags[CF] = (rdst + rsrc > 255); rdst += rsrc; break;
      case 0x10: flags[CF] = (rdst + rsrc > 255); rdst += rsrc + flags[CF]; break;
      case 0x20: rdst &= rsrc; break;
      case 0x30: rdst |= rsrc; break;
      case 0x40: rdst ^= rsrc; break;
      case 0x50: rdst *= rsrc; break;
      case 0x60:
        break;  // unary operation must be here
      case 0x70: rdst = rsrc; break;
      case 0x80:
        break;  // LPM operation must be here
      case 0x90: rdst = RAM[GetX() + (op & 0x0F)]; break;
      case 0xA0: rdst = PINS[(op >> 4) & 0x1F]; break;
      case 0xB0: PORTS[(op >> 4) & 0x1F] = rdst; break;
      case 0xC0: RAM[GetX() + (op & 0x0F)] = rdst; break;
      case 0xD0:
      case 0xE0: // CMP implementation, CPMC has not implemented yet
        if (rdst < rsrc) {
          flags[LF] = true; flags[EF] = false; flags[GF] = false;
        } else if (rdst == rsrc) {
          flags[LF] = false; flags[EF] = true; flags[GF] = false;
        } else if (rdst > rsrc) {
          flags[LF] = false; flags[EF] = false; flags[GF] = true;
        }
        break;
    }
    ip++;
    if (op < 0xA0)  // только эти операции изменяют регистры
      regs[dst] = rdst;
  } else if (op >= 0xF0 && op <= 0xFF) {
    uint8_t offset = cmd & 0xFF;
    cout << "offset: " << hex << (uint16_t)offset << endl;
    switch (op) {
      case 0xF0: stck.push(ip); ip += offset; break;      // CALL
      case 0xF1: ip += offset; break;                     // JMP
      case 0xF2: ip = stck.top(); stck.pop(); break;      // RET
      case 0xF3: if (flags[ZF]) ip += offset; break;      // JZ
      case 0xF4: if (flags[LF]) ip += offset; break;      // JL
      case 0xF5: if (flags[EF]) ip += offset; break;      // JE
      case 0xF6: if (!flags[EF]) ip += offset; break;     // JNE
      case 0xF8: if (!flags[ZF]) ip += offset; break;     // JNZ
      case 0xF9: if (flags[CF]) ip += offset; break;      // JC
      case 0xFA: if (!flags[CF]) ip += offset; break;     // JNC
      case 0xFB: if (flags[HCF]) ip += offset; break;     // JHC
      case 0xFC: if (!flags[HCF]) ip += offset; break;    // JHNC
      case 0xFD: stop = true; break;                      // STOP
      case 0xFE: stck.push(ip); ip = offset << 8; break;  // AFCALL
      case 0xFF: ip++; break;                             // NOP
    }
  } else {
    cout << "WTF?! Error opcode" << endl;
  }
}

int main(int argc, char* argv[]) {
  for (uint16_t ip = 0; ip < 256 && !stop;) {
    step(cmds[ip], ip);
  }

  return 0;
}
