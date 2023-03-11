from uc_inter import *
from uc_env import *
from uc_token import *

#import pdb

class Parser:
  def __init__(self, lexer):
    self.look = Token(0)
    self.top = None
    self.used = 0
    self.lexer = lexer
    self.move()

  def move(self):
    self.look = self.lexer.scan()
    print("Parser::move, look: " + self.look.toString() + ", type: " + type(self.look).__name__)

  def error(self, s):
    print("Parser::error")
    raise Exception("near line " + str(self.lexer.line) + ": " + s)

  def match(self, t):
    ival = ord(t) if type(t) is str else int(t)
    print("Parser::match(%d)" % ival)
    if self.look.tag == t:
      self.move()
    else:
      self.error("syntax error")

  def program(self):
    print("Parser::program")
    s = self.block()
    begin = s.newlabel()
    after = s.newlabel()
    s.emitlabel(begin)
    s.gen(begin, after)
    s.emitlabel(after)

  #pdb.set_trace()

  def block(self):  # block -> { decls stmts }
    print("Parser::block")
    self.match('{')
    savedEnv = self.top
    self.top = Env(self.top)
    self.decls()
    s = self.stmts()
    self.match('}')
    self.top = savedEnv
    return s

  def decls(self):
    print("Parser::decls")
    while self.look.tag == Tag.BASIC:  # D -> type ID ;
      p = self.type()
      tok = self.look
      self.match(Tag.ID)
      self.match(';')
      id = Id(tok, p, self.used)
      self.top.put( tok, id )
      self.used = self.used + p.width

  def type(self):
    print("Parser::type, look: " + self.look.toString())
    p = self.look  # get the copy of token
    self.match(Tag.BASIC)  # expect look.tag == Tag.BASIC 
    if self.look.tag != '[':
      return p  # T -> basic
    else:
      return dims(p)  # return array type

  def stmts(self):
    print("Parser::stmts")
    if self.look.tag == '}':
      return Stmt.Null
    else:
      return Seq(stmt(), stmts())

