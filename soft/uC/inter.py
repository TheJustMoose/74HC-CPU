
class Node:
  lexline = 0
  labels = 0

  def __init__(self):
    lexline = Lexer.line

  def error(self, s):
    raise Exception('near line {}: {}'.format(self.lexline, s))

  def newlabel(self):
    labels += 1
    return labels

  def emitlabel(self, i):
    print("L" + i + ":")

  def emit(s):
    print("\t" + s)

class Expr(Node):
  def __init__(self, tok, p):
    self.op = tok
    self.Type = p

  def gen(self):
    return self

  def reduce(self):
    return self

  def jumping(t, f):
    emitjumps(toString(), t, f)

  def emitjumps(self, test, t, f):
    if t != 0 and f != 0:
      emit("if " + test + " goto L" + t)
      emit("goto L" + f)
    elif t != 0:
      emit

