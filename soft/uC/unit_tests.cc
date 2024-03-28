#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "lexer.h"
#include "word.h"

using namespace std;

TEST_CASE("check Lexer") {
  CHECK(Lexer::If()->toString() == "if");

  stringstream ss("1 + 2");
  Lexer lex(ss);
  Token* t = lex.scan();
  CHECK( t );
  CHECK( t->tag() == Tag::tNUM );
}
