import os
import sys

from cpu import *

cop_to_name = {}

cop_mask = 0x0F
src_mask = 0x07 << 4
dst_mask = 0x07 << 7
ctype_mask = 0x03 << 10

def arithm_cmd():
  return 0

def jump_cmd():
  return 1

def ctrl_cmd():
  return 2

def transfer_cmd():
  return 3

def get_ctype(w):
  res = (w & ctype_mask) >> 10
  return res

def get_dst(w):
  res = (w & dst_mask) >> 7
  return res

def get_src(w):
  res = (w & src_mask) >> 4
  return res

def get_cop(w):
  res = (w & cop_mask)
  return res

def extract_cops():
  for c in cmds:
    cmd = cmds[c]
    uid = (cmd["TP"] << 10) + cmd["COP"]
    cop_to_name[uid] = c
    print(uid, cmd)

def get_cmd_size(w):
  ctype = get_ctype(w)
  cop = get_cop(w)
  name = cop_to_name[cop]
  if ctype == arithm_cmd():  # arithm instruction with const?
    return 2 if get_src(w) == src_regs["CONST"] else 1

  if ctype == jump_cmd():
    if name == "RET" or name == "IRET" or name == "CSIE":
      return 1
    else:
      return 2

  if ctype == ctrl_cmd():
    return 1

  if ctype == transfer_cmd():
    if name == "LOAD" or name == "IN":
      return 1
    elif name == "CFG":
      return 2
    else:  # STORE/OUT/XOUT
      if get_src(w) == src_regs["CONST"]:
        return 2
      else:
        return 1

def disasm(w):
  cop = w & 0x0F
  ctype = w & 0xC00
  name = cop_to_name[ctype + cop]
  return name

def dbg(bin):
  addr = 0
  while addr < len(bin):
    w = bin[addr]
    print("%03X %4s" % (w, disasm(w)))
    addr += get_cmd_size(w)
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
