#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

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

TEST_CASE("check COPs") {
  CodeLine cl1(1, "NOP");
  CHECK(cl1.generate_machine_code() == 0xFFFF);

  CodeLine cl2(1, "ADD R0, R0");
  CHECK(cl2.generate_machine_code() == 0x0000);

  CodeLine cl3(1, "ADD R1, R2");
  CHECK(cl3.generate_machine_code() == 0x0240);
}
