from tag import *

class Token:
  def __init__(self, t):
    self.tag = t

  def toString(self):
    return str(self.tag)

class Num(Token):
  def __init__(self, v):
    super().__init__(Tag.NUM)
    self.value = v

  def toString(self):
    return str(self.value)

class Word(Token):
  def __init__(self, s, tag):
    super().__init__(tag)
    self.lexeme = s

  def toString(self):
    return self.lexeme

  def Init():
    Word.And = Word("&&", Tag.AND)
