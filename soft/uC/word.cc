#include "word.h"

using namespace std;

Word::Word(std::string s, Tag tag)
  : Token(tag), lexeme_(s) {
}

string Word::toString() {
  return lexeme_;
}

// static
shared_ptr<Word> Word::And() {
  return shared_ptr<Word>( new Word( "&&", Tag::tAND ) );
}

shared_ptr<Word> Word::Or() {
  return shared_ptr<Word>( new Word( "||", Tag::tOR ) );
}

shared_ptr<Word> Word::Eq() {
  return shared_ptr<Word>( new Word( "==", Tag::tEQ ) );
}

shared_ptr<Word> Word::Ne() {
  return shared_ptr<Word>( new Word( "!=", Tag::tNE ) );
}

shared_ptr<Word> Word::Le() {
  return shared_ptr<Word>( new Word( "<=", Tag::tLE ) );
}

shared_ptr<Word> Word::Ge() {
  return shared_ptr<Word>( new Word( ">=", Tag::tGE ) );
}

shared_ptr<Word> Word::Minus() {
  return shared_ptr<Word>( new Word( "minus", Tag::tMINUS ) );
}

shared_ptr<Word> Word::Temp() {
  return shared_ptr<Word>( new Word( "t", Tag::tTEMP ) );
}
