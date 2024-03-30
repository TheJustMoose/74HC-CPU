#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <cctype>

#include "lexer.h"
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

  shared_ptr<Token> t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tNUM );
  CHECK( t->toString() == "1" );
}

TEST_CASE("check Lexer") {
  stringstream ss("1 + 234");
  Lexer lex(ss);

  shared_ptr<Token> t = lex.scan();
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
  // end of file / stream /etc
  t = lex.scan();
  CHECK( t == nullptr );
}

TEST_CASE("check dictionary") {
  stringstream ss("word word word");
  Lexer lex(ss);

  shared_ptr<Token> t1 = lex.scan();
  REQUIRE( t1 );
  shared_ptr<Token> t2 = lex.scan();
  REQUIRE( t2 );
  shared_ptr<Token> t3 = lex.scan();
  REQUIRE( t3 );

  // we should have only one copy of word
  CHECK( t1 == t2 );
  CHECK( t2 == t3 );
}
