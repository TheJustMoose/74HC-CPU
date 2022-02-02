import os
import sys

from cpu import *

cop_to_name = {}
dst_to_name = {}
src_to_name = {}
port_to_name = {}
pin_to_name = {}

class State:
  R0 = 0
  R1 = 0
  R2 = 0
  R3 = 0
  R4 = 0
  R5 = 0
  R6 = 0
  R7 = 0

state = State()

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

def extract_regs():
  for r in dst_regs:
    idx = dst_regs[r]
    dst_to_name[idx] = r

  for r in src_regs:
    idx = src_regs[r]
    src_to_name[idx] = r

  for p in dst_ports:
    idx = dst_ports[p]
    port_to_name[idx] = p

  for p in src_ports:
    idx = src_ports[p]
    pin_to_name[idx] = p

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

def disasm(w, w2):
  name = cop_to_name[w & (ctype_mask + cop_mask)]
  res = name

  cop = get_cop(w)
  ctype = get_ctype(w)
  if ctype == arithm_cmd():  # arithm instruction with const?
    res += " " + dst_to_name[get_dst(w)]
    if get_src(w) == src_regs["CONST"]:
      res += ", " + str(w2)
    else:
      res += ", " + src_to_name[get_src(w)]

  if ctype == jump_cmd():
    if name[0] == "J" or name == "CALL":
      res += " " + str(w2)

  if ctype == transfer_cmd():
    if name == "LOAD" or name == "IN":
      res += " " + dst_to_name[get_dst(w)]
    elif name == "CFG":
      res += " " + str(w2)
      res += ", " + src_to_name[get_src(w)]
    elif name == "STORE":
      if get_src(w) == src_regs["CONST"]:
        res += ", " + str(w2)
      else:
        res += ", " + src_to_name[get_src(w)]
    else:  # OUT/XOUT
      res += " " + port_to_name[get_dst(w)]
      if get_src(w) == src_regs["CONST"]:
        res += ", " + str(w2)
      else:
        res += ", " + src_to_name[get_src(w)]

  return res

def dbg(bin):
  addr = 0
  while addr < len(bin):
    w = bin[addr]
    w2 = bin[addr + 1] if addr < len(bin) - 1 else 0
    print("%04X:  %03X   %s" % (addr, w, disasm(w, w2)))
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
    extract_regs()

    bin = load(fname)
    dbg(bin)

main()
