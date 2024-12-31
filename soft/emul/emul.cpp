/*
  Cmd system of 74hcpu:

|-----------------------------------------------|f|
|   4   +  3 + 1 + 3  +    5    = 16            |l|
|   HIGH BYTE   |    LOW BYTE   |   HIGH BYTE   |a|
|0 1 2 3 4 5 6 7 8 9 A B C D E F|    (again)    |g|
|-----------------------------------------------|s|
|   ADD | DST |C| SRC |-|Z|z|I|i| 00 = 0000 0000|*|
|  ADDC | DST |C| SRC |F|Z|z|I|i| 10 = 0001 0000|*|
|   AND | DST |C| SRC |-|Z|z|I|i| 20 = 0010 0000|*|
|    OR | DST |C| SRC |-|Z|z|I|i| 30 = 0011 0000|*|
|   XOR | DST |C| SRC |-|Z|z|I|i| 40 = 0100 0000|*|
|   MUL | DST |C| SRC |-|Z|z|I|i| 50 = 0101 0000|*|
|   UNO | DST |0|-|TYP|F|-|-|-|-| 60 = 0110 0000|*|
|   MOV | DST |C| SRC |*|Z|z|I|i| 70 = 0111 0000| |
|   LPM | DST |W|EXT|D|U|OFFSET4| 80 = 1000 0000| |
|    LD | DST |0|EXT|D|U|OFFSET4| 90 = 1001 0000| |
|    IN | DST |  PORT   |-|-|I|i| A0 = 1010 0000| |
|-------------|7-8-9-A-B|-------|---------------|-|
|   OUT | SRC |  PORT   |O|o|X|x| B0 = 1011 0000| |
|    ST | SRC |0|EXT|D|U|OFFSET4| C0 = 1100 0000| |
|   CMP | DST |C| SRC |-|   -   | D0 = 1101 0000|+|
|  CMPC | DST |C| SRC |-|   -   | E0 = 1110 0000|+|
| BRNCH |  CALL | 8 bit OFFSET  | F0 = 1111 0000| |
| BRNCH |   JMP | 8 bit OFFSET  | F1 = 1111 0001| |
| BRNCH |   RET | 8 bit +STACK  | F2 = 1111 0010| |
| BRNCH |    JZ | 8 bit OFFSET  | F3 = 1111 0011| |
| BRNCH |    JL | 8 bit OFFSET  | F4 = 1111 0100| |
| BRNCH |   JNE | 8 bit OFFSET  | F5 = 1111 0101| |
| BRNCH |    JE | 8 bit OFFSET  | F6 = 1111 0110| |
| BRNCH |    JG | 8 bit OFFSET  | F7 = 1111 0111| |
| BRNCH |    JC | 8 bit OFFSET  | F8 = 1111 1000| |
| BRNCH |   JNZ | 8 bit OFFSET  | F9 = 1111 1001| |
| BRNCH |   JNC | 8 bit OFFSET  | FA = 1111 1010| |
| BRNCH |   JHC | 8 bit OFFSET  | FB = 1111 1011| |
| BRNCH |  JNHC | 8 bit OFFSET  | FC = 1111 1100| |
| BRNCH |  STOP |   0000 0000   | FD = 1111 1101| |
| BRNCH |AFCALL | Hi 8 bit ADDR | FE = 1111 1110| |
| BRNCH |   NOP |   1111 1111   | FF = 1111 1111| |
|-----------------------------------------------|-|

*/

#include "emul.h"

#include <exception>
#include <iostream>

using namespace std;

Cops GetCopFromMachineCode(uint16_t machine_code) {
  uint8_t cop = machine_code >> 8;  // HI byte

  // we need LO nibble of code for branches only
  if (static_cast<Cops>(cop & 0xF0) != Cops::cBRANCH)
    cop &= 0xF0;  // another operations have zero low nibble

  return static_cast<Cops>(cop);
}

unique_ptr<Instruction> CreateFromMachineCode(uint16_t machine_code) {
  switch (GetCopFromMachineCode(machine_code)) {
    case Cops::cADD: return make_unique<Add>(machine_code);
    case Cops::cADDC: return make_unique<AddC>(machine_code);
    case Cops::cAND: return make_unique<And>(machine_code);
    case Cops::cOR: return make_unique<Or>(machine_code);
    case Cops::cXOR: return make_unique<Xor>(machine_code);
    case Cops::cMUL: return make_unique<Mul>(machine_code);
    case Cops::cUNO: return make_unique<Uno>(machine_code);
    case Cops::cMOV: return make_unique<Mov>(machine_code);
    case Cops::cLPM: return make_unique<Lpm>(machine_code);
    case Cops::cLD: return make_unique<Ld>(machine_code);
    case Cops::cIN: return make_unique<In>(machine_code);
    case Cops::cOUT: return make_unique<Out>(machine_code);
    case Cops::cST: return make_unique<St>(machine_code);
    case Cops::cCMP: return make_unique<Cmp>(machine_code);
    case Cops::cCMPC: return make_unique<CmpC>(machine_code);
    default: throw exception("Unknown COP");
  }
}

Reg& Bank::GetRegByNum(uint8_t RegNum) {
  switch (RegNum) {
    case 0: return R0;
    case 1: return R1;
    case 2: return R2;
    case 3: return R3;
    case 4: return R4;
    case 5: return R5;
    case 6: return R6;
    case 7: return R7;
    default: throw exception("Unknown RegNum");
  }
}

Reg& RegByNum::operator[](uint8_t RegNum) {
  return cpu_->ActiveBank().GetRegByNum(RegNum);
}

Bank& CPU::ActiveBank() {
  if (active_bank_num_ == 0)
    return bank0;
  else
    return bank1;
}

Reg& BinaryInstruction::LeftOp(CPU* cpu) {
  if (!cpu)
    throw exception("Pointer to CPU is nullptr");

  INSTRUCTION ins {};
  ins.machine_code = code();
  cout << "BinaryInstruction code: " << code() << endl;
  return cpu->R[ins.bin_ins.high.dst];
}

uint8_t BinaryInstruction::RightOp(CPU* cpu) {
  if (!cpu)
    throw exception("Pointer to CPU is nullptr");

  INSTRUCTION ins {};
  ins.machine_code = code();
  if (ins.bin_ins.high.cnst)
    return ins.bin_ins.low.Const;
  else
    return cpu->R[ins.bin_ins.low.Flags.src];
}

void Add::Execute(CPU* cpu) {
  cout << Name() << " " << LeftOp(cpu).name() << ", " << (int)RightOp(cpu) << endl;
}

void AddC::Execute(CPU* cpu) {
  cout << Name() << " " << LeftOp(cpu).name() << ", " << (int)RightOp(cpu) << endl;
}

void And::Execute(CPU* cpu) {
  cout << Name() << " " << LeftOp(cpu).name() << ", " << (int)RightOp(cpu) << endl;
}

void Or::Execute(CPU* cpu) {
  cout << Name() << " " << LeftOp(cpu).name() << ", " << (int)RightOp(cpu) << endl;
}

void Xor::Execute(CPU* cpu) {
  cout << Name() << " " << LeftOp(cpu).name() << ", " << (int)RightOp(cpu) << endl;
}

void Mul::Execute(CPU* cpu) {
  cout << Name() << " " << LeftOp(cpu).name() << ", " << (int)RightOp(cpu) << endl;
}

void Uno::Execute(CPU*) {
  cout << "Uno" << endl;
}

void Mov::Execute(CPU* cpu) {
  cout << Name() << " " << LeftOp(cpu).name() << ", " << (int)RightOp(cpu) << endl;
}

void Lpm::Execute(CPU*) {
  cout << "Lpm" << endl;
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

void Cmp::Execute(CPU* cpu) {
  cout << Name() << " " << (int)LeftOp(cpu) << ", " << (int)RightOp(cpu) << endl;
}

void CmpC::Execute(CPU* cpu) {
  cout << Name() << " " << (int)LeftOp(cpu) << ", " << (int)RightOp(cpu) << endl;
}
