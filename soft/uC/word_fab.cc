#include "word_fab.h"

#include "tag.h"
#include "token.h"

using namespace std;

shared_ptr<Word> And() {
  return shared_ptr<Word>( new Word( "&&", Tag::tAND ) );
}

shared_ptr<Word> Or() {
  return shared_ptr<Word>( new Word( "||", Tag::tOR ) );
}

shared_ptr<Word> Eq() {
  return shared_ptr<Word>( new Word( "==", Tag::tEQ ) );
}

shared_ptr<Word> Ne() {
  return shared_ptr<Word>( new Word( "!=", Tag::tNE ) );
}

shared_ptr<Word> Le() {
  return shared_ptr<Word>( new Word( "<=", Tag::tLE ) );
}

shared_ptr<Word> Ge() {
  return shared_ptr<Word>( new Word( ">=", Tag::tGE ) );
}

shared_ptr<Word> Minus() {
  return shared_ptr<Word>( new Word( "minus", Tag::tMINUS ) );
}

shared_ptr<Word> Temp() {
  return shared_ptr<Word>( new Word( "t", Tag::tTEMP ) );
}
