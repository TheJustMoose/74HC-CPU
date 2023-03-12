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
      idt = Id(tok, p, self.used)
      self.top.put(tok, idt)
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
      return Seq(self.stmt(), self.stmts())

  def stmt(self):
    print("Parser::stmt")
    if self.look.tag == ';':
      self.move()
      return Stmt.Null
    if self.look.tag == '{':
      return self.block()
    else:
      return self.assign()

  def assign(self):
    t = self.look
    self.match(Tag.ID)
    idt = self.top.get(t)
    if idt == None:
      error(t.toString() + " undeclared")

    stmt = None
    if self.look.tag == '=':  # S -> id = E ;
      self.move()
      stmt = Set(idt, self.bool())
    else:                     # S -> L = E ;
      x = offset(idt)
      self.match('=')
      stmt = SetElem(x, self.bool())

    self.match(';')
    return stmt

  def bool(self):
    x = self.join()
    while self.look.tag == Tag.OR:
      tok = self.look
      self.move()
      x = Or(tok, x, self.join())
    return x

  def join(self):
    x = self.equality()
    while self.look.tag == Tag.AND:
      tok = self.look
      self.move()
      x = And(tok, x, self.equality())
    return x

  def equality(self):
    x = self.rel()
    while self.look.tag == Tag.EQ or self.look.tag == Tag.NE:
      tok = self.look
      self.move()
      x = Rel(tok, x, self.rel())
    return x

  def rel(self):
    print("Parser::rel")
    x = self.expr()
    relops = ['<', Tag.LE, Tag.GE, '>']
    if self.look.tag in relops:
      tok = self.look
      move()
      return Rel(tok, x, self.expr())
    else:
      return x

  def expr(self):
    pass
