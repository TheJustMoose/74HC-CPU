#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "consts.h"
#include "emul.h"

TEST_CASE("check size of structures") {
  CHECK_EQ(sizeof(Flags), 1);
  CHECK_EQ(sizeof(Cops), 1);
  CHECK_EQ(sizeof(BIN_INS_FLAGS), 1);
  CHECK_EQ(sizeof(BIN_INS_LOW_BYTE), 1);
  CHECK_EQ(sizeof(BIN_INS_HIGH_BYTE), 1);

  CHECK_EQ(sizeof(BIN_INS), 2);
  CHECK_EQ(sizeof(INSTRUCTION), 2);
}

TEST_CASE("check GetCopFromMachineCode") {
  CHECK_EQ(GetCopFromMachineCode(0x0000), Cops::cADD);
  CHECK_EQ(GetCopFromMachineCode(0x0001), Cops::cADD);
  CHECK_EQ(GetCopFromMachineCode(0x0002), Cops::cADD);  // have to remove LSB bits
  CHECK_EQ(GetCopFromMachineCode(0x0202), Cops::cADD);  // have to remove LSB bits

  CHECK_EQ(GetCopFromMachineCode(0x1000), Cops::cADDC);
  CHECK_EQ(GetCopFromMachineCode(0x710F), Cops::cMOV);
  CHECK_EQ(GetCopFromMachineCode(0xE000), Cops::cCMPC);
  CHECK_EQ(GetCopFromMachineCode(0xF000), Cops::cBRANCH);
  CHECK_EQ(GetCopFromMachineCode(0xF000), Cops::cCALL);
  CHECK_EQ(GetCopFromMachineCode(0xF100), Cops::cJMP);
  CHECK_EQ(GetCopFromMachineCode(0xFE00), Cops::cAFCALL);
  CHECK_EQ(GetCopFromMachineCode(0xFF00), Cops::cNOP);
}

TEST_CASE("check binary instruction bit fields") {
// |   MOV | DST |C| SRC |*|Z|z|I|i| 70 0111 0000| |
//     MOV   R0,     0x0F
//    0111   000  1  0000 1111 == 0x710F
  INSTRUCTION ins {};
  ins.machine_code = 0x710F;

  CHECK_EQ(ins.bin_ins.high.cop, 7);
  CHECK_EQ(ins.bin_ins.high.dst, 0);
  CHECK_EQ(ins.bin_ins.high.cnst, 1);
}

TEST_CASE("check RegByNum") {
  Bank b;
  CHECK_EQ(&b.R0, &b.R0);

  Reg& r0 = b.GetRegByNum(0);
  CHECK_EQ(&r0, &b.R0);

  Reg& r7 = b.GetRegByNum(7);
  CHECK_EQ(&r7, &b.R7);

  CHECK_THROWS(b.GetRegByNum(10));
}
