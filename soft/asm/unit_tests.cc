#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

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

  // check labels
  CHECK(pre.StripLine("label: mov  ax, bx  ; test cmd") == "label: mov ax, bx");
  CHECK(pre.StripLine("  LSR   R0  ") == "LSR R0");

  // check directives
  CHECK(pre.StripLine(".org 100h") == ".org 100h");
  CHECK(pre.StripLine("  .org 100h ; comment") == ".org 100h");

  // check different spaces
  CHECK(pre.StripLine("\t\tLSR R0  \n") == "LSR R0");
}

TEST_CASE("check .def detection") {
  map<int, string> lines {
    {1, "mov r0, r1"},
    {2, ".def ACC R0"}
  };

  Preprocessor pre;
  CHECK(!pre.Preprocess(nullptr));
  CHECK(pre.Preprocess(&lines));
  CHECK(lines.size() == 1);
}
