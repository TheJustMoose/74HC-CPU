#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "assm.h"
#include "preprocessor.h"

using namespace std;

TEST_CASE("check preprocessor cleaner") {
  Preprocessor pre;

  CHECK(pre.IsSpace(' '));
  CHECK(pre.IsSpace('\t'));
  CHECK(pre.IsSpace('\n'));
  CHECK(pre.IsSpace('\r'));
  CHECK(!pre.IsSpace('A'));

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
  Preprocessor pre;

  CHECK(pre.Split("test").size() == 1);

  vector<string> v = pre.Split("test test");
  REQUIRE(v.size() == 2);
  CHECK(v[0] == "test");
  CHECK(v[1] == "test");

  vector<string> c1 = pre.Split("add r0, 10");
  REQUIRE(c1.size() == 4);
  CHECK(c1[0] == "add");
  CHECK(c1[1] == "r0");
  CHECK(c1[2] == ",");
  CHECK(c1[3] == "10");

  vector<string> c2 = pre.Split(" add  r0 , 10 ");
  REQUIRE(c2.size() == 4);
  CHECK(c2[0] == "add");
  CHECK(c2[1] == "r0");
  CHECK(c2[2] == ",");
  CHECK(c2[3] == "10");

  vector<string> c3 = pre.Split(".org 100h");
  REQUIRE(c3.size() == 2);
  CHECK(c3[0] == ".org");
  CHECK(c3[1] == "100h");

  vector<string> c4 = pre.Split(".def\tACC\tR0\n");
  REQUIRE(c4.size() == 3);
  CHECK(c4[0] == ".def");
  CHECK(c4[1] == "ACC");
  CHECK(c4[2] == "R0");
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

TEST_CASE("check COPs") {
  CodeLine cl(1, "NOP");
  CHECK(cl.generate_machine_code() == 0xFFFF);
}
