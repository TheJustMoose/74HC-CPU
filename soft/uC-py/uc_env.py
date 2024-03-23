
class Env:
  table = None
  prev = None

  def __init__(self, n):
    self.table = {}
    self.prev = n

  def put(self, w, i):
    self.table[w] = i

  def get(self, w):
    e = self
    while e != None:
      r = e.table.get(w)
      if r != None:
        return r
      e = e.prev
    return None
