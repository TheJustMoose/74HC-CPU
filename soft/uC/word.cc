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
  static unique_ptr<Word> ptr = make_unique<Word>( "&&", Tag::AND );
  return ptr.get();
}

Word* Word::Or() {
  static unique_ptr<Word> ptr = make_unique<Word>( "||", Tag::OR );
  return ptr.get();
}

Word* Word::Eq() {
  static unique_ptr<Word> ptr = make_unique<Word>( "==", Tag::EQ );
  return ptr.get();
}

Word* Word::Ne() {
  static unique_ptr<Word> ptr = make_unique<Word>( "!=", Tag::NE );
  return ptr.get();
}

Word* Word::Le() {
  static unique_ptr<Word> ptr = make_unique<Word>( "<=", Tag::LE );
  return ptr.get();
}

Word* Word::Ge() {
  static unique_ptr<Word> ptr = make_unique<Word>( ">=", Tag::GE );
  return ptr.get();
}

Word* Word::Minus() {
  static unique_ptr<Word> ptr = make_unique<Word>( "minus", Tag::MINUS );
  return ptr.get();
}

Word* Word::True() {
  static unique_ptr<Word> ptr = make_unique<Word>( "true", Tag::TRUE );
  return ptr.get();
}

Word* Word::False() {
  static unique_ptr<Word> ptr = make_unique<Word>( "false", Tag::FALSE );
  return ptr.get();
}

Word* Word::Temp() {
  static unique_ptr<Word> ptr = make_unique<Word>( "t", Tag::TEMP );
  return ptr.get();
}
