from uc_inter import *
from uc_env import *
from uc_token import *

import pdb

class Parser:
  def __init__(self, lexer):
    self.look = Token(0)
    self.top = None
    self.used = 0
    self.lexer = lexer
    self.move()

  def move(self):
    self.look = self.lexer.scan()

  def error(self, s):
    raise Exception("near line " + str(self.lexer.line) + ": " + s)

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
    pdb.set_trace()
    self.decls()
    s = self.stmts()
    self.match('}')
    self.top = savedEnv
    return s

  def decls(self):
    while self.look.tag == Tag.BASIC:  # D -> type ID ;
      p = self.type()
      tok = self.look
      self.match(Tag.ID)
      self.match(';')
      id = Id(Word(tok), p, used)
      self.top.put( tok, id )
      self.used = self.used + p.width

  def type(self):
    self.match(Tag.BASIC)  # expect look.tag == Tag.BASIC 
    if self.look.tag != '[':
      return self.look  # T -> basic
    else:
      return dims(self.look)  # return array type

  def stmts(self):
    if self.look.tag == '}':
      return Stmt.Null
    else:
      return Seq(stmt(), stmts())

