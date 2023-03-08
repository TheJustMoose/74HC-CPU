from inter import *
from env import *
from token import *

class Parser:
  def __init__(self, lexer):
    self.look = Token(0)
    self.top = None
    self.used = 0
    self.lexer = lexer
    self.move()

  def move(self):
    self.look = self.lexer.scan()

  def match(self, t):
    if self.look.tag == t:
      self.move()
    else:
      self.error("syntax error")

  def program(self):
    s = self.block()
    begin = s.newlabel()
    after = s.newlabel()
    s.emitlabel(begin)
    s.gen(begin, after)
    s.emitlabel(after)

  def block(self):  # block -> { decls stmts }
    self.match('{')
    savedEnv = self.top
    self.top = Env(self.top)
    self.decls()
    s = self.stmts()
    self.match('}')
    self.top = savedEnv
    return s

  def decls(self):
    while self.look.tag == Tag.BASIC:  # D -> type ID ;
      p = self.type()
      tok = look
      self.match(Tag.ID)
      self.match(';')
      id = Id(Word(tok), p, used)
      self.top.put( tok, id )
      self.used = self.used + p.width

  def type(self):
    p = Type(self.look)  # expect look.tag == Tag.BASIC 
    self.match(Tag.BASIC);
    if self.look.tag != '[':
      return p  # T -> basic
    else:
      return dims(p)  # return array type

  def stmts(self):
    if self.look.tag == '}':
      return Stmt.Null
    else:
      return Seq(stmt(), stmts())

