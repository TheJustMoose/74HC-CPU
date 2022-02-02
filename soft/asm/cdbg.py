import os
import sys

from cpu import *

cop_to_name = {}

def extract_cops():
  for c in cmds:
    cmd = cmds[c]
    uid = (cmd["TP"] << 10) + cmd["COP"]
    cop_to_name[uid] = c
    print(uid, cmd)

def disasm(w):
  cop = w & 0x0F
  ctype = w & 0xC00
  name = cop_to_name[ctype + cop]
  return name

def dbg(bin):
  for b in bin:
    print("%03X %4s" % (b, disasm(b)))
  return

def load(fname):
  with open(fname, "r") as f:
    s = f.read()
    words = s.split()
    print("Load %d machine code words" % len(words))
    res = []
    for w in words:
      res.append(int(w, 16))
    return res

def main():
  if __name__ == "__main__":
    if len(sys.argv) < 2:
      print("To use type:\ncdbg.py your_source.bin\n")
      return

    fname = sys.argv[1]
    if not os.path.exists(fname):
      print("%s file doesn't exist" % fname)
      return

    extract_cops()

    bin = load(fname)
    dbg(bin)

main()
