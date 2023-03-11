from uc_tag import *

class Token:
  def __init__(self, t):
    self.tag = t

  def toString(self):
    try:
      return str(self.tag) + ' ' + self.tag.name
    finally:
      return str(self.tag)

class Num(Token):
  def __init__(self, v):
    super().__init__(Tag.NUM)
    self.value = v

  def toString(self):
    return str(self.value) + ' ' + self.tag.name

class Word(Token):
  def __init__(self, s, tag):
    super().__init__(tag)
    self.lexeme = s

  def toString(self):
    return self.lexeme + ' ' + self.tag.name

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
    return str(self.value) + ' ' + self.tag.name

class Type(Word):
  def __init__(self, s, tag, w):
    super().__init__(s, tag)
    self.width = w

  @staticmethod
  def Init():
    Type.INT = Type("int", Tag.BASIC, 4)
    Type.FLOAT = Type("float", Tag.BASIC, 8)
    Type.CHAR = Type("char", Tag.BASIC, 1)
    Type.BOOL = Type("bool", Tag.BASIC, 1)

  @staticmethod
  def Numeric(p):
    if p == Type.CHAR or p == Type.INT or p == Type.FLOAT:
      return True
    return False

  @staticmethod
  def max(p1, p2):
    print("IMPLEMENT ME!!")
    return p1

class Array(Type):
  def __init__(sz, p):
    super().__init__("[]", Tag.Index, sz*p.width)
    self.size = sz
    self.of = p

  def toString():
    return "[" + str(size) + "]" + of.toString()

