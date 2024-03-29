#include "word.h"

#include <memory>

using namespace std;

Word::Word(std::string s, Tag tag)
  : Token(tag), lexeme_(s) {
}

string Word::toString() {
  return lexeme_;
}

Word* Word::And() {
  static unique_ptr<Word> ptr = make_unique<Word>( "&&", Tag::tAND );
  return ptr.get();
}

Word* Word::Or() {
  static unique_ptr<Word> ptr = make_unique<Word>( "||", Tag::tOR );
  return ptr.get();
}

Word* Word::Eq() {
  static unique_ptr<Word> ptr = make_unique<Word>( "==", Tag::tEQ );
  return ptr.get();
}

Word* Word::Ne() {
  static unique_ptr<Word> ptr = make_unique<Word>( "!=", Tag::tNE );
  return ptr.get();
}

Word* Word::Le() {
  static unique_ptr<Word> ptr = make_unique<Word>( "<=", Tag::tLE );
  return ptr.get();
}

Word* Word::Ge() {
  static unique_ptr<Word> ptr = make_unique<Word>( ">=", Tag::tGE );
  return ptr.get();
}

Word* Word::Minus() {
  static unique_ptr<Word> ptr = make_unique<Word>( "minus", Tag::tMINUS );
  return ptr.get();
}

Word* Word::Temp() {
  static unique_ptr<Word> ptr = make_unique<Word>( "t", Tag::tTEMP );
  return ptr.get();
}
