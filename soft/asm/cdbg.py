import os
import sys
import msvcrt  # plz fix it to use in Linux *ROFL*
import random

from cpu import *

cop_to_name = {}
dst_to_name = {}
src_to_name = {}
port_to_name = {}
pin_to_name = {}

REGS0 = [0, 0, 0, 0, 0, 0, 0, 0]
REGS1 = [0, 0, 0, 0, 0, 0, 0, 0]
PORT = [0, 0, 0, 0]
RAM = [0]*65536

bank0 = True

CF = False  # carry flag
ZF = False  # zero flag
SF = False  # shift flag

LF = False  # less flag
EF = False  # equal flag
GF = False  # greater flag

IP = 0
stack = []

cop_mask = 0x0F
src_mask = 0x07 << 4
dst_mask = 0x07 << 7
ctype_mask = 0x03 << 10

def push(addr):
  stack.append(addr)
  return

def pop():
  return stack.pop(-1)

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
    #print(uid, cmd)

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
  name = cop_to_name[(ctype << 10) + cop]

  if ctype == arithm_cmd():  # arithm instruction with const?
    return 2 if get_src(w) == src_regs["CONST"] else 1

  if ctype == jump_cmd():
    if name == "RET" or name == "IRET" or name == "SIE" or name == "SIZ":
      return 1
    else:
      return 2

  if ctype == ctrl_cmd():
    return 1

  if ctype == transfer_cmd():
    if name == "LOAD" or name == "STORE" or name == "IN":
      return 1
    elif name == "CFG":
      return 2
    else:  # OUT/XOUT
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
      res += " %04X" % w2

  if ctype == transfer_cmd():
    if name == "LOAD" or name == "STORE":
      res += " " + dst_to_name[get_dst(w)]
    elif name == "IN":
      res += " " + dst_to_name[get_dst(w)]
      res += ", " + pin_to_name[get_src(w)]
    elif name == "CFG":
      res += " " + str(w2)
      res += ", " + src_to_name[get_src(w)]
    else:  # OUT/XOUT
      res += " " + port_to_name[get_dst(w)]
      if get_src(w) == src_regs["CONST"]:
        res += ", " + str(w2)
      else:
        res += ", " + src_to_name[get_src(w)]

  return res

def dump_human_regs():
  global bank0
  bank = REGS0 if bank0 else REGS1
  a = (bank[7] << 8) + bank[6]
  b = (bank[5] << 8) + bank[4]
  c = (bank[3] << 8) + bank[2]
  d = (bank[1] << 8) + bank[0]
  res = "%5d %5d %5d %5d" % (a, b, c, d)
  return res

def dump_regs():
  regs = ""
  global bank0
  bank = REGS0 if bank0 else REGS1
  for r in bank:
    regs = ("%02X " % r) + regs
  pre = "b0 " if bank0 else "b1 "
  res = pre + regs

  port = ""
  for p in PORT:
    port = ("%02X " % p) + port
  res += " | p " + port

  bub = chr(4)
  res += " |"
  res += " CF:" + bub if CF else " CF: "
  res += " ZF:" + bub if GF else " ZF: "
  res += " SF:" + bub if SF else " SF: "

  res += " LF:" + bub if LF else " LF: "
  res += " EF:" + bub if EF else " EF: "
  res += " GF:" + bub if GF else " GF: "
  return res

def dump_mem():
  tail = RAM[65536 - 24:]
  res = " m "
  for t in tail:
    res += "%02X " % t
  return res

def execute_cmd(w, w2):
  global IP, CF, ZF, SF, LF, EF, GF

  ctype = get_ctype(w)
  cop = get_cop(w)
  name = cop_to_name[(ctype << 10) + cop]

  global bank0
  bank = REGS0 if bank0 else REGS1

  if ctype == arithm_cmd():
    dst = get_dst(w)
    src = get_src(w)
    rval = w2 & 0xFF if src == src_regs["CONST"] else bank[src]
    if name == "AND":
      bank[dst] = bank[dst] & rval
      ZF = bank[dst] == 0
    elif name == "OR":
      bank[dst] = bank[dst] | rval
      ZF = bank[dst] == 0
    elif name == "XOR":
      bank[dst] = bank[dst] ^ rval
      ZF = bank[dst] == 0
    elif name == "ADD" or name == "ADDC":
      bank[dst] = bank[dst] + rval
      ZF = bank[dst] == 0
      if name == "ADDC" and CF:
        bank[dst] += 1
      if bank[dst] > 0xFF:
        bank[dst] &= 0xFF
        CF = True
      else:
        CF = False
    elif name == "MOV":
      bank[dst] = rval
      ZF = bank[dst] == 0
    elif name == "CLR" or name == "CLR2":
      bank[dst] = 0
      ZF = bank[dst] == 0
    elif name == "INV" or name == "INV2":
      bank[dst] = ~rval
      ZF = bank[dst] == 0
    elif name == "LSL" or name == "LSL2":
      t = SF
      SF = (rval & 0x80) > 0
      bank[dst] = (rval << 1) & 0xFF
      if t:
        bank[dst] |= 0x01
      ZF = bank[dst] == 0
    elif name == "LSR" or name == "LSR2":
      t = SF
      SF = (rval & 0x01) > 0
      bank[dst] = (rval >> 1) & 0xFF
      if t:
        bank[dst] |= 0x80
      ZF = bank[dst] == 0
    elif name == "SET" or name == "SET2":
      bank[dst] = 0xFF
      ZF = bank[dst] == 0
    elif name == "MUL":
      res = bank[dst]*rval
      reg_num = dst & 0x6
      bank[reg_num] = res & 0xFF
      bank[reg_num + 1] = (res >> 8) & 0xFF
    elif name == "CMP":
      LF = bank[dst] < rval
      EF = bank[dst] == rval
      GF = bank[dst] > rval
    # copy r0:r1 cause in real life it's one pair without banks
    if bank0:
      REGS1[0] = REGS0[0]
      REGS1[1] = REGS0[1]
    else:
      REGS0[0] = REGS1[0]
      REGS0[1] = REGS1[1]

  if ctype == jump_cmd():
    if name == "JMP":
      IP = w2
      return

    if name == "JC" and CF:
      IP = w2
      return
    if name == "JNC" and not CF:
      IP = w2
      return

    if name == "JS" and SF:
      IP = w2
      return

    if name == "JE" and EF:
      IP = w2
      return
    if name == "NJE" and not EF:
      IP = w2
      return

    if name == "JL" and LF:
      IP = w2
      return
    if name == "JG" and GF:
      IP = w2
      return

    if name == "JZ" and ZF:
      IP = w2
      return
    if name == "JNZ" and not ZF:
      IP = w2
      return

    if name == "CALL":
      push(IP + 2)  # call cmd size should be 2
      IP = w2
      return
    if name == "RET" or name == "IRET":
      IP = pop()
      return

    if name == "SIE" and EF:
      IP += get_cmd_size(w) + 2 # += 3
      return
    if name == "SIZ" and ZF:
      IP += get_cmd_size(w) + 2 # += 3
      return

  if ctype == ctrl_cmd():
    if name == "CLRF":
      CF = False
      ZF = False
      LF = False
      EF = True
      GF = False
      SF = False

    if name == "NOP":
      print("NOP!")

    if name == "BANK0":
      bank0 = True
    if name == "BANK1":
      bank0 = False

    if name == "RESET":
      IP = 0
      return

  if ctype == transfer_cmd():
    if name == "OUT":
      dst = get_dst(w)
      src = get_src(w)
      rval = w2 & 0xFF if src == src_regs["CONST"] else bank[src]
      PORT[dst] = rval
    if name == "STORE":
      dst = get_dst(w)
      addr = (bank[7] << 8) + bank[6]
      RAM[addr] = bank[dst]
    if name == "LOAD":
      dst = get_dst(w)
      addr = (bank[7] << 8) + bank[6]
      bank[dst] = RAM[addr]
    # copy r0:r1 cause in real life it's one pair without banks
    if bank0:
      REGS1[0] = REGS0[0]
      REGS1[1] = REGS0[1]
    else:
      REGS0[0] = REGS1[0]
      REGS0[1] = REGS1[1]

  IP += get_cmd_size(w)

  return

def dump(bin):
  addr = 0
  while addr < len(bin):
    w = bin[addr]
    w2 = bin[addr + 1] if addr < len(bin) - 1 else 0
    sz = get_cmd_size(w)
    print("%04X:  %03X %d  %-20s | %s" % (addr, w, sz, disasm(w, w2), dump_regs()))
    addr += sz

  print("")

def dbg(bin):
  while True:
    if IP < len(bin):
      w = bin[IP]
      w2 = bin[IP + 1] if IP < len(bin) - 1 else 0
      sz = get_cmd_size(w)
      print(" " * 39 + dump_human_regs())
      print("%04X:  %03X %d  %-20s | %s" % (IP, w, sz, disasm(w, w2), dump_regs()))
      print("step - g, abort - a                | %s" % dump_mem())

      answ = msvcrt.getch()
      if answ == b'a':
        return
      execute_cmd(w, w2)
      print("")
    else:
      print("Finished")
      break

  return

def init_ram():
  global RAM
  for i in range(0, 65536):
    RAM[i] = random.randint(0, 255)

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
    init_ram()
    bin = load(fname)
    #dump(bin)
    dbg(bin)

main()
