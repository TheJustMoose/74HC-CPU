#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "lexer.h"
#include "word.h"

using namespace std;

TEST_CASE("check Lexer") {
  CHECK(Lexer::If()->toString() == "if");

  //CHECK(pre.IsSpace(' '));
}
