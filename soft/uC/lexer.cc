#include "lexer.h"

#include "tag.h"

using namespace std;

Lexer::Lexer() {
  reserve( make_unique<Word>("if",    Tag::IF)    );
  reserve( make_unique<Word>("else",  Tag::ELSE)  );
  reserve( make_unique<Word>("while", Tag::WHILE) );
  reserve( make_unique<Word>("do",    Tag::DO)    );
  reserve( make_unique<Word>("break", Tag::BREAK) );

  reserve( Word::True() );
  reserve( Word::False() );
  reserve( Type::Int  );
  reserve( Type::Char  );
  reserve( Type::Bool );
  reserve( Type::Float );
}

void Lexer::reserve(Word* w) {
  if (!w) {
    cerr << "Word is NULL" << endl;
    return;
  }

  words_[w->lexeme()] = w;
}

void Lexer::readch() {
}

bool Lexer::readch(char c) {
}

Token Lexer::scan() {
}
