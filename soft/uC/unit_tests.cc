#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <cctype>

#include "id.h"
#include "env.h"
#include "lexer.h"
#include "num.h"
#include "op.h"
#include "parser.h"
#include "real.h"
#include "token.h"

using namespace std;

TEST_CASE("check cpp lib") {
  CHECK( isdigit('9') != 0 );
  CHECK( isdigit('1') != 0 );
  CHECK( isdigit('0') != 0 );
  CHECK( isdigit(' ') == 0 );
  CHECK( isdigit(0) == 0 );

  CHECK( to_string(1) == "1");
  CHECK( to_string(1.0) == "1.000000");
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

TEST_CASE("check Real") {
  Real r(1.5);
  CHECK( r.toString() == "1.500000" );  // no good, no good ;)

  stringstream ss("1.5");
  Lexer lex(ss);

  Token* t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tREAL );
  CHECK( t->toString() == "1.500000" );
}

TEST_CASE("check Lexer") {
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

  // end of file / stream /etc
  t = lex.scan();
  CHECK( t == nullptr );
}

TEST_CASE("check dictionary") {
  stringstream ss("word word word");
  Lexer lex(ss);

  Token* t1 = lex.scan();
  REQUIRE( t1 );
  Token* t2 = lex.scan();
  REQUIRE( t2 );
  Token* t3 = lex.scan();
  REQUIRE( t3 );

  // we should have only one copy of word
  CHECK( t1 == t2 );
  CHECK( t2 == t3 );

  CHECK( t1->tag() == Tag::tID );
}

TEST_CASE("check key words") {
  stringstream ss("if do else");
  Lexer lex(ss);

  Token* t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tIF );

  t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tDO );

  t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tELSE );
}

TEST_CASE("check id chars") {
  stringstream ss("test  t0  t_0st  __und__");
  Lexer lex(ss);

  Token* t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tID );
  CHECK( t->toString() == "test" );

  t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tID );
  CHECK( t->toString() == "t0" );

  t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tID );
  CHECK( t->toString() == "t_0st" );

  t = lex.scan();
  REQUIRE( t );
  CHECK( t->tag() == Tag::tID );
  CHECK( t->toString() == "__und__" );
}

TEST_CASE("check Env class") {
  Env e;
  Token* t = new Token('a');
  Word w("tmp", Tag::tID);
  Word* int_w = Lexer::get_word("int");

  Id* id = new Id(&w, static_cast<Type*>(int_w), 10);
  e.put(t, id);

  CHECK( e.get(t) );
  CHECK( e.get(t) == id );
  delete id;
}

TEST_CASE("check Parser") {
  stringstream ss("{ int a; }");
  Lexer lex(ss);
  Parser p(&lex);
  p.program();
}

TEST_CASE("check Op") {
  Op op(nullptr, nullptr);
}
