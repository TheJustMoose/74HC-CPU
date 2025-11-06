#include <doctest.h>

#include <map>
#include <string>

#include "preprocessor.h"

using namespace std;

TEST_CASE("check preprocessor cleaner") {
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
