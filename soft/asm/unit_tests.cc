#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <map>
#include <string>

#include "assm.h"
#include "preprocessor.h"
#include "str_util.h"

using namespace std;

TEST_CASE("check preprocessor cleaner") {
  CHECK(IsSpace(' '));
  CHECK(IsSpace('\t'));
  CHECK(IsSpace('\n'));
  CHECK(IsSpace('\r'));
  CHECK(!IsSpace('A'));

  Preprocessor pre;

  // check empty lines
  CHECK(pre.StripLine("") == "");
  CHECK(pre.StripLine(" ") == "");
  CHECK(pre.StripLine("  ") == "");
  CHECK(pre.StripLine("\n") == "");

  // check many spaces in many places
  CHECK(pre.StripLine("a") == "a");
  CHECK(pre.StripLine(" a") == "a");
  CHECK(pre.StripLine("a ") == "a");
  CHECK(pre.StripLine(" a ") == "a");
  CHECK(pre.StripLine("  a  ") == "a");

  CHECK(pre.StripLine("a b") == "a b");
  CHECK(pre.StripLine("a  b") == "a b");
  CHECK(pre.StripLine("a   b") == "a b");
  CHECK(pre.StripLine(" a b") == "a b");
  CHECK(pre.StripLine("a b ") == "a b");
  CHECK(pre.StripLine("  a b  ") == "a b");

  // check comment removing
  CHECK(pre.StripLine("LSR R0 ; comment ") == "LSR R0");
  CHECK(pre.StripLine("LSR R0;comment ") == "LSR R0");
  CHECK(pre.StripLine("; comment ") == "");
  CHECK(pre.StripLine(";") == "");
  CHECK(pre.StripLine("\n;") == "");

  // check labels
  CHECK(pre.StripLine("label: mov  ax, bx  ; test cmd") == "label: mov ax, bx");
  CHECK(pre.StripLine("  LSR   R0  ") == "LSR R0");

  // check directives
  CHECK(pre.StripLine(".org 100h") == ".org 100h");
  CHECK(pre.StripLine("  .org 100h ; comment") == ".org 100h");

  // check different spaces
  CHECK(pre.StripLine("\t\tLSR R0  \n") == "LSR R0");
  CHECK(pre.StripLine("LSR\tR0") == "LSR\tR0");

  CHECK(pre.StripLine(";.org 1000h") == "");
}

TEST_CASE("check split") {
  CHECK(Split("test").size() == 1);

  vector<string> v = Split("test test");
  REQUIRE(v.size() == 2);
  CHECK(v[0] == "test");
  CHECK(v[1] == "test");

  vector<string> c1 = Split("add r0, 10");
  REQUIRE(c1.size() == 4);
  CHECK(c1[0] == "add");
  CHECK(c1[1] == "r0");
  CHECK(c1[2] == ",");
  CHECK(c1[3] == "10");

  vector<string> c2 = Split(" add  r0 , 10 ");
  REQUIRE(c2.size() == 4);
  CHECK(c2[0] == "add");
  CHECK(c2[1] == "r0");
  CHECK(c2[2] == ",");
  CHECK(c2[3] == "10");

  vector<string> c3 = Split(".org 100h");
  REQUIRE(c3.size() == 2);
  CHECK(c3[0] == ".org");
  CHECK(c3[1] == "100h");

  vector<string> c4 = Split(".def\tACC\tR0\n");
  REQUIRE(c4.size() == 3);
  CHECK(c4[0] == ".def");
  CHECK(c4[1] == "ACC");
  CHECK(c4[2] == "R0");
}

TEST_CASE("check split command parts") {
  vector<string> t1 = SplitToCmdParts("MOV a, b");
  CHECK(t1.size() == 3);
  CHECK(t1[0] == "MOV");
  CHECK(t1[1] == "A");  // Args converted to upper during split
  CHECK(t1[2] == "B");

  vector<string> t2 = SplitToCmdParts("ST X+1, R0");
  CHECK(t2.size() == 3);
  CHECK(t2[0] == "ST");
  CHECK(t2[1] == "X+1");
  CHECK(t2[2] == "R0");

  vector<string> t3 = SplitToCmdParts("LD R1, Y-1");
  CHECK(t3.size() == 3);
  CHECK(t3[0] == "LD");
  CHECK(t3[1] == "R1");
  CHECK(t3[2] == "Y-1");

  vector<string> t4 = SplitToCmdParts("STOP");
  CHECK(t4.size() == 3);
  CHECK(t4[0] == "STOP");
  CHECK(t4[1] == "");
  CHECK(t4[2] == "");
}

TEST_CASE("check .def detection & simple defines") {
  map<int, string> lines {
    {1, "add ACC, r1"},
    {2, "PUSH r0"},
    {3, "PUSH r7"},
    {10, ".def ACC R0"},
    {11, ".def PUSH(r) ST SPD, r"},
    {13, ";.org 1000h"}
  };

  Preprocessor pre;
  CHECK(!pre.Preprocess(nullptr));

  CHECK(pre.Preprocess(&lines));
  REQUIRE(lines.size() == 4);
  // now all string items separated by space
  CHECK(lines[1] == "add R0 , r1");
  CHECK(lines[2] == "ST SPD , r0");
  CHECK(lines[3] == "ST SPD , r7");
  CHECK(lines[4] == "");
}

TEST_CASE("check labels") {
  map<int, string> lines {
    {1, "label:PUSH r0"},
    {2, "lsr r0"},
    {11, ".def PUSH(r) ST SPD, r"}
  };

  Preprocessor pre;
  CHECK(!pre.Preprocess(nullptr));

  CHECK(pre.Preprocess(&lines));
  REQUIRE(lines.size() == 2);
  // now all string items separated by space
  CHECK(lines[1] == "label:ST SPD , r0");
  CHECK(lines[2] == "lsr r0");
}

TEST_CASE("check names getter") {
  CHECK(Names::RegFromName("R0") == rR0);
  CHECK(Names::RegFromName("R7") == rR7);
}

TEST_CASE("check str_util") {
  CHECK(NormalizeLine("  ADD   R0,   R1") == "ADD R0, R1");
  CHECK(NormalizeLine("\"  ADD   R0,   R1\"") == "\"  ADD   R0,   R1\"");

  int val;
  CHECK(!StrToInt("", &val));
  CHECK(!StrToInt("test", &val));

  CHECK(StrToInt("1", &val));
  CHECK(1 == val);

  CHECK(StrToInt("10", &val));
  CHECK(10 == val);

  CHECK(StrToInt("999999", &val));
  CHECK(999999 == val);

  CHECK(StrToInt("10H", &val));
  CHECK(16 == val);

  CHECK(StrToInt("0X10", &val));
  CHECK(16 == val);

  CHECK(StrToInt("0X1FFF", &val));
  CHECK(0x1FFF == val);

  CHECK(StrToInt("0O177", &val));
  CHECK(127 == val);

  CHECK(StrToInt("0B1010", &val));
  CHECK(10 == val);

  CHECK(StrToInt("0B0000", &val));
  CHECK(0 == val);

  CHECK(StrToInt("0B1111", &val));
  CHECK(15 == val);
}

TEST_CASE("check arithm COPs") {
  CodeLine cl1(1, "NOP");
  CHECK(cl1.generate_machine_code() == 0xFFFF);

  // 0000 000 0 000 00000
  CodeLine cl2(1, "ADD R0, R0");
  CHECK(cl2.generate_machine_code() == 0x0000);

  // 0000 001 0 010 00000
  CodeLine cl3(1, "ADD R1, R2");
  CHECK(cl3.generate_machine_code() == 0x0240);

  // 0000 010 0 011 00000
  CodeLine cl4(1, "ADD R2, R3");
  CHECK(cl4.generate_machine_code() == 0x0460);

  // 0001 010 0 011 00000
  CodeLine cl5(1, "ADDC R2, R3");
  CHECK(cl5.generate_machine_code() == 0x1460);

  // 0010 011 0 100 00000
  CodeLine cl6(1, "AND R3, R4");
  CHECK(cl6.generate_machine_code() == 0x2680);

  // 0011 100 0 101 00000
  CodeLine cl7(1, "OR R4, R5");
  CHECK(cl7.generate_machine_code() == 0x38A0);

  // 0100 101 0 110 00000
  CodeLine cl8(1, "XOR R5, R6");
  CHECK(cl8.generate_machine_code() == 0x4AC0);

  // 0101 110 0 111 00000
  CodeLine cl9(1, "MUL R6, R7");
  CHECK(cl9.generate_machine_code() == 0x5CE0);

  // 0110 111 0 000 00000
  CodeLine clB(1, "INV R7");
  CHECK(clB.generate_machine_code() == 0x6E00);

  // 0110 111 0 001 00000
  CodeLine clA(1, "SWAP R7");
  CHECK(clA.generate_machine_code() == 0x6E20);

  // 0110 111 0 010 00000
  CodeLine clC(1, "LSR R7");
  CHECK(clC.generate_machine_code() == 0x6E40);

  // 0110 111 0 011 00000
  CodeLine clD(1, "LSRC R7");
  CHECK(clD.generate_machine_code() == 0x6E60);

  // 0111 000 0 111 00000
  CodeLine clE(1, "MOV R0, R7");
  CHECK(clE.generate_machine_code() == 0x70E0);
}

TEST_CASE("check ROM COPs") {
  // LPM  DST W SR DU OFST
  // 1000 000 0 00 00 0000
  CodeLine cl1(1, "LPM R0, X");
  CHECK(cl1.generate_machine_code() == 0x8000);

  // 1000 101 0 00 00 0000
  CodeLine cl2(1, "LPM R5, X");
  CHECK(cl2.generate_machine_code() == 0x8A00);

  // 1000 000 0 01 00 0000
  CodeLine cl3(1, "LPM R0, Y");
  CHECK(cl3.generate_machine_code() == 0x8040);

  // 1000 000 0 10 00 0000
  CodeLine cl4(1, "LPM R0, Z");  // R0 = *Z;
  CHECK(cl4.generate_machine_code() == 0x8080);

  // 1000 000 0 11 00 0000
  CodeLine cl5(1, "LPM R0, SP");
  CHECK(cl5.generate_machine_code() == 0x80C0);

  // 1000 110 0 11 00 0001
  CodeLine cl6(1, "LPM R6, SP+1");  // R6 = *(SP + 1);
  CHECK(cl6.generate_machine_code() == 0x8CC1);

  // 1000 110 0 11 00 0111
  CodeLine cl7(1, "LPM R6, SP+7");  // R6 = *(SP + 7);
  CHECK(cl7.generate_machine_code() == 0x8CC7);

  // 1000 110 0 11 00 1111
  CodeLine cl8(1, "LPM R6, SP-1");
  CHECK(cl8.generate_machine_code() == 0x8CCF);

  // 1000 110 0 11 00 1110
  CodeLine cl9(1, "LPM R6, SP-2");
  CHECK(cl9.generate_machine_code() == 0x8CCE);

  // 1000 110 0 11 00 1001
  CodeLine clA(1, "LPM R6, SP-7");
  CHECK(clA.generate_machine_code() == 0x8CC9);

  // 1000 110 0 11 00 1000
  CodeLine clB(1, "LPM R6, SP-8");
  CHECK(clB.generate_machine_code() == 0x8CC8);

  // LPM  DST W SR DU OFST
  // 1000 101 0 00 01 0000
  CodeLine clC(1, "LPM R5, XI");  // R5 = *X++; in C++ notation (Load with post-increment)
  CHECK(clC.generate_machine_code() == 0x8A10);

  // 1000 101 0 00 10 0000
  CodeLine clD(1, "LPM R5, XD");  // R5 = *X--; in C++ notation (Load with post-decrement)
  CHECK(clD.generate_machine_code() == 0x8A20);

  // 1000 101 0 00 10 0001
  CodeLine clE(1, "LPM R5, XD+1");  // R5 = *(X + 1); X--;  in C++ notation (Load with post-decrement and displacement)
  CHECK(clE.generate_machine_code() == 0x8A21);
}

TEST_CASE("check RAM COPs") {
  // LD   DST - SR DU OFST
  // 1001 000 0 00 00 0000
  CodeLine cl1(1, "LD R0, X");
  CHECK(cl1.generate_machine_code() == 0x9000);

  // ST   SRC - DS DU OFST
  // 1100 000 0 00 00 0000
  CodeLine cl2(1, "ST X, R0");
  CHECK(cl2.generate_machine_code() == 0xC000);

  // 1100 000 0 00 00 0101
  CodeLine cl3(1, "ST X+5, R0");
  CHECK(cl3.generate_machine_code() == 0xC005);

  // 1100 111 0 01 00 0000
  CodeLine cl4(1, "ST Y, R7");
  CHECK(cl4.generate_machine_code() == 0xCE40);
}

TEST_CASE("check I/O COPs") {
  // IN   DST  PORT ZzIi
  // 1010 011 00010 0000
  CodeLine cl1(1, "IN R3, PINS1");
  CHECK(cl1.generate_machine_code() == 0xA620);

  // OUT  SRC  PORT OoXx
  // 1011 111 01011 0000  // PORT9 have number 11, see port_names
  CodeLine cl2(1, "OUT PORT9, R7");
  CHECK(cl2.generate_machine_code() == 0xBEB0);
}

TEST_CASE("check branches COPs") {
  // 1111 0010 00000000
  CodeLine cl1(1, "LBL: RET");
  CHECK(cl1.generate_machine_code() == 0xF200);
  // 1111 0000 00000000
  CodeLine cl2(2, "CALL LBL");  // fortunately, LBL address is 0
  CHECK(cl2.generate_machine_code() == 0xF000);

  // 1111 0001 00001010
  CodeLine cl3(1, "JMP LBL");
  // Try to set LBL offset (from current address)
  cl3.update_machine_code( map<string, uint16_t> { {"LBL", 10} } );
  CHECK(cl3.generate_machine_code() == 0xF10A);

  // 1111 0001 11111111
  CodeLine cl4(1, "JMP LBL");
  cl4.set_address(0x0010);
  // Try to set LBL offset (from current address)
  cl4.update_machine_code( map<string, uint16_t> { {"LBL", 0x000F} } );
  CHECK(cl4.generate_machine_code() == 0xF1FF);  // jmp to previous instruction
}
