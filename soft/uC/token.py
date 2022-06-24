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

  @staticmethod
  def Init():
    Word.AND = Word("&&", Tag.AND)
    Word.OR = Word("||", Tag.OR)
    Word.EQ = Word("==", Tag.EQ)
    Word.NE = Word("!=", Tag.NE)
    Word.LE = Word("<=", Tag.LE)
    Word.GE = Word(">=", Tag.GE)
    Word.MINUS = Word("minus", Tag.MINUS)
    Word.TRUE = Word("true", Tag.TRUE)
    Word.FALSE = Word("false", Tag.FALSE)
    Word.TEMP = Word("temp", Tag.TEMP)

class Real(Token):
  def __init__(self, v):
    super().__init__(Tag.REAL)
    self.value = v

  def toString(self):
    return str(self.value)

