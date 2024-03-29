#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <cctype>

#include "lexer.h"
#include "num.h"
#include "word.h"

using namespace std;

TEST_CASE("check cpp lib") {
  CHECK( isdigit('9') != 0 );
  CHECK( isdigit('1') != 0 );
  CHECK( isdigit('0') != 0 );
  CHECK( isdigit(' ') == 0 );
  CHECK( isdigit(0) == 0 );

  CHECK( to_string(1) == "1");
  CHECK( to_string(321) == "321");
}

TEST_CASE("check Num") {
  Num n(1);
  CHECK( n.toString() == "1" );
  Token* tn = &n;
  CHECK( tn->toString() == "1" );

  stringstream ss("1");
  Lexer lex(ss);

  Token* t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tNUM );
  CHECK( t->toString() == "1" );
}

TEST_CASE("check Lexer") {
  CHECK(Lexer::If()->toString() == "if");

  stringstream ss("1 + 234");
  Lexer lex(ss);

  Token* t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tNUM );
  CHECK( t->toString() == "1" );

  t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag('+') );

  t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tNUM );
  CHECK( t->toString() == "234" );

  t = lex.scan();
  CHECK( t == nullptr );
}
