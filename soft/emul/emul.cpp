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

#include <exception>
#include <iostream>

using namespace std;

unique_ptr<Instruction> CreateFromMachineCode(uint16_t machine_code) {
  uint8_t cop = machine_code >> 8;  // HI byte
  // we need LO nibble of code for branches only
  if (static_cast<Cops>(cop & 0xF0) != Cops::BRANCH)
    cop &= 0xF0;  // another operations have zero low nibble

  switch (static_cast<Cops>(cop)) {
    case Cops::ADD: return make_unique<Add>(machine_code);
    case Cops::ADDC: return make_unique<AddC>(machine_code);
    case Cops::AND: return make_unique<And>(machine_code);
    case Cops::OR: return make_unique<Or>(machine_code);
    case Cops::XOR: return make_unique<Xor>(machine_code);
    case Cops::MUL: return make_unique<Mul>(machine_code);
    case Cops::UNO: return make_unique<Uno>(machine_code);
    case Cops::MOV: return make_unique<Mov>(machine_code);
    case Cops::LPM: return make_unique<Lpm>(machine_code);
    case Cops::LD: return make_unique<Ld>(machine_code);
    case Cops::IN: return make_unique<In>(machine_code);
    case Cops::OUT: return make_unique<Out>(machine_code);
    case Cops::ST: return make_unique<St>(machine_code);
    case Cops::CMP: return make_unique<Cmp>(machine_code);
    case Cops::CMPC: return make_unique<CmpC>(machine_code);
    default: throw exception("Unknown COP");
  }
}

struct BIN_INS {
  uint16_t cop : 4;  // code of operation
  uint16_t dst : 3;  // destination register
  uint16_t cnst : 1; // const or register
  uint16_t src : 3;  // source register
  uint16_t frc : 1;  // force to set CF flag
  uint16_t Z : 1;    // zero hi nibble
  uint16_t z : 1;    // zero lo nibble
  uint16_t I : 1;    // invert hi nibble
  uint16_t i : 1;    // invert lo nibble
};

union INSTRUCTION {
  uint16_t machine_code;
  BIN_INS bin_ins;
};

uint8_t BinaryInstruction::LeftOp(CPU* cpu) {
  if (!cpu)
    throw exception("Pointer to CPU is nullptr");

  INSTRUCTION ins;
  ins.machine_code = code();
  return ins.bin_ins.dst;
}

uint8_t BinaryInstruction::RightOp(CPU* cpu) {
  if (!cpu)
    throw exception("Pointer to CPU is nullptr");

  INSTRUCTION ins;
  ins.machine_code = code();
  return ins.bin_ins.src;
}

void Add::Execute(CPU* cpu) {
  cout << Name() << " " << (int)LeftOp(cpu) << ", " << (int)RightOp(cpu) << endl;
}

void AddC::Execute(CPU*) {
  cout << "AddC" << endl;
}

void And::Execute(CPU*) {
  cout << "And" << endl;
}

void Or::Execute(CPU*) {
  cout << "Or" << endl;
}

void Xor::Execute(CPU*) {
  cout << "Xor" << endl;
}

void Mul::Execute(CPU*) {
  cout << "Mul" << endl;
}

void Uno::Execute(CPU*) {
  cout << "Uno" << endl;
}

void Mov::Execute(CPU*) {
  cout << "Mov" << endl;
}

void Lpm::Execute(CPU*) {
  cout << "Lmp" << endl;
}

void Ld::Execute(CPU*) {
  cout << "Ld" << endl;
}

void In::Execute(CPU*) {
  cout << "In" << endl;
}

void Out::Execute(CPU*) {
  cout << "Out" << endl;
}

void St::Execute(CPU*) {
  cout << "St" << endl;
}

void Cmp::Execute(CPU*) {
  cout << "Cmp" << endl;
}

void CmpC::Execute(CPU*) {
  cout << "CmpC" << endl;
}
