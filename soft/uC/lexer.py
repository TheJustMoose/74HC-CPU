import sys
from tag import *
from token import *

class Lexer:
  line = 1
  peek = ' '
  words = []

  def reserve(self, w):
    self.words.append(w)

  def __init__(self):
    self.reserve(Word("if", Tag.IF))
    self.reserve(Word("else", Tag.ELSE))
    self.reserve(Word("while", Tag.WHILE))
    self.reserve(Word("do", Tag.DO))
    self.reserve(Word("break", Tag.BREAK))
    self.reserve(Word.TRUE)
    self.reserve(Word.FALSE)
    #self.reserve(Type.INT)
    #self.reserve(Type.CHAR)
    #self.reserve(Type.BOOL)
    #self.reserve(Type.FLOAT)

  def log(self):
    for w in self.words:
      print("word:", w.toString())

  def readche(self):
    self.peek = sys.stdin.read(1)

  def readch(self, c):
    self.readche()
    if self.peek != c:
      return False
    self.peek = ' '
    return True

  def scan(self):
    while self.readche():
      if self.peek == ' ' or self.peek == '\t':
        continue
      elif self.peek == '\n':
        self.line += 1
      else:
        break

    if self.peek == '&':
      if self.readch('&'):
        return Word.AND
