import sys
from uc_tag import *
from uc_token import *

class Lexer:
  line = 1
  peek = ' '
  words = []

  def reserve(self, w):
    self.words.append(w)

  def word_in_words(self, s):
    r = list(filter(lambda w: w.lexeme == s, self.words))
    if len(r) == 0:
      return None
    return r[0]

  def __init__(self):
    self.reserve(Word("if", Tag.IF))
    self.reserve(Word("else", Tag.ELSE))
    self.reserve(Word("while", Tag.WHILE))
    self.reserve(Word("do", Tag.DO))
    self.reserve(Word("break", Tag.BREAK))
    self.reserve(Word.TRUE)
    self.reserve(Word.FALSE)
    self.reserve(Type.INT)
    self.reserve(Type.CHAR)
    self.reserve(Type.BOOL)
    self.reserve(Type.FLOAT)

  def log(self):
    for w in self.words:
      print("word:", w.toString(), type(w))

  def readche(self):
    self.peek = sys.stdin.read(1)

  def readch(self, c):
    self.readche()
    if self.peek != c:
      return False
    self.peek = ' '
    return True

  def scan(self):
    while True:
      if self.peek == ' ' or self.peek == '\t' or self.peek == '\r':
        self.readche()
      elif self.peek == '\n':
        self.line += 1
        self.readche()
      else:
        break

    if self.peek == '&':
      return Word.AND if self.readch('&') else Token('&')

    if self.peek == '|':
      return Word.OR if self.readch('|') else Token('|')

    if self.peek == '=':
      return Word.EQ if self.readch('=') else Token('=')

    if self.peek == '!':
      return Word.NE if self.readch('=') else Token('!')

    if self.peek == '<':
      return Word.LE if self.readch('=') else Token('<')

    if self.peek == '>':
      return Word.GE if self.readch('=') else Token('>')

    if self.peek.isdigit():
      v = 0
      while True:
        v = 10*v + int(self.peek)
        self.readche()
        if not self.peek.isdigit():
          break
      if self.peek != '.':
        return Num(v)
      x = v*1.0
      d = 10.0
      while True:
        self.readche()
        if not self.peek.isdigit():
          break
        x += int(self.peek) / d
        d *= 10.0
      return Real(x)

    if self.peek.isalpha():
      buf = ""
      while True:
        buf += self.peek
        self.readche()
        if not self.peek.isalnum():
          break

      exist = self.word_in_words(buf)
      if exist:
        print("found: " + type(exist).__name__)
        return exist

      w = Word(buf, Tag.ID)
      self.words.append(w)
      return w

    tok = Token(self.peek)
    self.peek = ' '
    return tok
