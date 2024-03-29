from uc_lexer import *
from uc_token import *

class Node:
  lexline = 0
  labels = 0

  def __init__(self):
    self.lexline = Lexer.line

  def error(self, s):
    raise Exception('near line {}: {}'.format(self.lexline, s))

  def newlabel(self):
    self.labels += 1
    return self.labels

  def emitlabel(self, i):
    print("L" + str(i) + ":")

  def emit(self, s):
    print("\t" + s)


class Expr(Node):
  def __init__(self, tok, p):
    self.op = tok
    self.Type = p

  def gen(self):
    return self

  def reduce(self):
    return self

  def jumping(self, t, f):
    emitjumps(self.toString(), t, f)

  def emitjumps(self, test, t, f):
    if t != 0 and f != 0:
      emit("if " + test + " goto L" + t)
      emit("goto L" + f)
    elif t != 0:
      emit("if " + test + " goto L" + t)
    elif f != 0:
      emit("iffalse " + test + " goto L" + f)
    #else:
    # nothing since both t and f fall through

  def toString(self):
    return self.op.toString()


class Stmt(Node):
  @staticmethod
  def Init():
    Stmt.Null = Stmt()
    Stmt.Enclosing = Stmt.Null  # used for break stmts

  def __init__(self):
    super().__init__()

  def gen(self, b, a):
    return self


class Seq(Stmt):
  def __init__(self, s1, s2):
    self.stmt1 = s1
    self.stmt2 = s2

  def gen(self, b, a):
    if self.stmt1 == Stmt.Null:
      self.stmt2.gen(b, a)
    elif self.stmt2 == Stmt.Null:
      self.stmt1.gen(b, a)
    else:
      label = self.newlabel()
      self.stmt1.gen(b, label)
      self.emitlabel(label)
      self.stmt2.gen(label, a)


class Set(Stmt):
  def __init__(self, i, x):
    self.idt = i
    self.expr = x
    if self.check(self.idt.Type, self.expr.Type) == None:
      self.error("type error")

  def check(self, p1, p2):
    if Type.Numeric(p1) and Type.Numeric(p2):
      return p2
    elif p1 == Type.BOOL and p2 == Type.BOOL:
      return p2
    else:
      return None

  def gen(self, b, a):
    self.emit(self.idt.toString() + " = " + self.expr.gen().toString())


class Id(Expr):
  def __init__(self, idt, p, b):
    super().__init__(idt, p)
    self.offset = b


class Op(Expr):
  def __init__(self, tok, p):
    super().__init__(tok, p)

  def reduce(self):
    x = gen()
    t = Temp(self.Type)
    emit(t.toString() + " = " + x.toString())
    return t


class Arith(Op):
  def __init__(self, tok, x1, x2):
    super().__init__(tok, None)
    self.expr1 = x1
    self.expr2 = x2
    self.Type = Type.max(self.expr1.Type, self.expr2.Type)
    if self.Type == None:
      self.error("type error")

  def gen(self):
    return Arith(self.op, self.expr1.reduce(), self.expr2.reduce())

  def toString(self):
    return self.expr1.toString() + " " + self.op.toString() + " " + self.expr2.toString()


class Temp(Expr):
  count = 0  # static
  number = 0
  def __init__(self, p):
    super().__init__(Word.Temp, p)
    Temp.count += 1  # static
    self.number = Temp.count

  def toString(self):
    return "t" + self.number


class Unary(Op):
  def __init__(self, tok, x):  # process unari minus
    super().__init__(tok, None)
    self.expr = x
    self.Type = Type.max(Type.INT, self.expr.Type)
    if self.Type == None:
      self.error("Type error")

  def gen(self):
    return Unary(self.op, self.expr.reduce())

  def toString(self):
    return self.op.toString() + " " + self.expr.toString()


class Constant(Expr):
  def __init__(self, tok, p):
    super().__init__(tok, p)
  # alternate constructor here

  @staticmethod
  def Init():
    Constant.TRUE = Constant(Word.TRUE, Type.BOOL)
    Constant.FALSE = Constant(Word.FALSE, Type.BOOL)

  def jumping(self, t, f):
    if self == Constant.TRUE and t != 0:
      emit("goto L" + t)
    elif self == Constant.FALSE and f != 0:
      emit("goto L" + f)


class Logical(Expr):
  def __init__(self, tok, x1, x2):
    super().__init_(tok, None)
    self.expr1 = x1
    self.expr2 = x2
    self.Type = check(expr1.Type, expr2.Type)
    if self.Type == None:
      error("Type error")

  def check(self, p1, p2):
    if p1 == Type.BOOL and p2 == Type.BOOL:
      return Type.BOOL
    else:
      return None

  def gen(self):
    f = newlabel()
    a = newlabel()
    temp = Temp(self.Type)
    self.jumping(0, f)
    emit(temp.toString() + " = true")
    emit("goto L" + a)
    emitlabel(f)
    emit(temp.toString() + " = false")
    emitlabel(a)
    return temp

  def toString(self):
    return expr1.toString() + " " + op.toString() + " " + expr2.toString()


class Or(Logical):
  def __init__(self, tok, x1, x2):
    super().__init__(tok, x1, x2)

  def jumping(self, t, f):
    label = t if t != 0 else newlabel()
    expr1.jumping(label, 0)
    expr2.jumping(t, f)
    if t == 0:
      emitlabel(label)


class And(Logical):
  def __init__(self, tok, x1, x2):
    super().__init__(tok, x1, x2)

  def jumping(self, t, f):
    label = f if f != 0 else newlabel()
    expr1.jumping(0, label)
    expr2.jumping(t, f)
    if f == 0:
      emitlabel(label)


class Not(Logical):
  def __init__(self, tok, x1, x2):
    super().__init__(tok, x1, x2)

  def jumping(self, t, f):
    expr2.jumping(t, f)

  def toString(self):
    return op.toString() + " " + expr2.toString()


class Rel(Logical):
  def __init__(self, tok, x1, x2):
    super().__init__(tok, x1, x2)

  def check(self, p1, p2):
    if isinstance(p1, Array) or isinstance(p2, Array):
      return None
    elif p1 == p2:
      return Type.BOOL
    else:
      return None

  def jumping(self, t, f):
    a = expr1.reduce()
    b = expr2.reduce()
    test = a.toString() + " " + op.toString() + " " + b.toString()
    emitjumps(test, t, f)


class Access(Op):
  def __init__(self, a, i, p):
    # p - type of the array item after align??
    super().__init__(Word("[]", Tag.INDEX), p)
    self.array = a
    self.index = i

  def gen(self):
    return Access(array, index.reduce(), Type)

  def jumping(self, t, f):
    emitjumps(reduce(), toString(), t, f)

  def toString(self):
    return array.toString() + " [ " + index.toString() + " ]"
