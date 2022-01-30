import sys
import os

# available command
# name | code | ctype | args
cmds = {
# binary
"AND": {"COP": 0, "TP": 0, "ARGS": 2},
"OR": {"COP": 1, "TP": 0, "ARGS": 2},
"XOR": {"COP": 2, "TP": 0, "ARGS": 2},
"MUL": {"COP": 3, "TP": 0, "ARGS": 2},
"ADD": {"COP": 4, "TP": 0, "ARGS": 2},
"ADDC": {"COP": 5, "TP": 0, "ARGS": 2},
"CMP": {"COP": 6, "TP": 0, "ARGS": 2},
"CMPC": {"COP": 7, "TP": 0, "ARGS": 2},
# unary
"CLR": {"COP": 8, "TP": 0, "ARGS": 1},
"NEG": {"COP": 9, "TP": 0, "ARGS": 1},
"LSL": {"COP": 10, "TP": 0, "ARGS": 1},
"LSR": {"COP": 11, "TP": 0, "ARGS": 1},
"MIR": {"COP": 12, "TP": 0, "ARGS": 1},
"MOV": {"COP": 13, "TP": 0, "ARGS": 2},
"SWAB": {"COP": 14, "TP": 0, "ARGS": 1},
"SET": {"COP": 15, "TP": 0, "ARGS": 1},
# jump
"JC": {"COP": 5, "TP": 1, "ARGS": 1},
"JNC": {"COP": 6, "TP": 1, "ARGS": 1},
"JMP": {"COP": 8, "TP": 1, "ARGS": 1},
"CALL": {"COP": 9, "TP": 1, "ARGS": 1},
"RET": {"COP": 10, "TP": 1, "ARGS": 0},
# transfer
"OUT": {"COP": 9, "TP": 3, "ARGS": 2},
}

regs = {
"R0": 0,
"R1": 1,
"R2": 2,
"R3": 3,
"R4": 4,
"R5": 5,
"R6": 6,
"R7": 7,
"CONST": 4,
"PIN0": 5,
"PIN1": 6,
"PORT0": 7,
}

labels = {}
label_of_line = {}
parsed_cmd = []
have_errors = False

def cmd_ok(parts):
  name = parts[0]
  cmd = cmds[name]
  args = cmd["ARGS"]
  if len(parts) - 1 != args:
    print("Error. Wait for %d args in %s" % (args, name))
    return False
  if args > 1 and parts[1] not in regs:
    print("Unknown register %s in '%s'" % (parts[1], " ".join(parts)))

  return True

def read_and_prepare(fname):
  res = []
  with open(fname) as f:
    lines = f.readlines()
    for l in lines:
      pos = l.find(';')
      if pos != -1:  # remove comments
        l = l[:pos]
      l = l.strip()  # remove spaces
      l = l.upper()
      pos = l.find(':')
      if pos != -1: # split comments into two lines
        label = l[:pos+1]
        res.append(label)
        l = l[pos+1:].strip()
      if len(l) > 0:
        l = l.replace(',', ' ')
        res.append(l)
  return res

def extract_labels(lines):
  res = []
  if lines[-1].find(':') != -1:
    print("Error. Labels in last line is not allowed.")
    return res
  for idx, l in enumerate(lines):
    if idx + 1 < len(lines) and \
       l.find(':') != -1 and \
       lines[idx + 1].find(':') != -1:
      print("Error. Only one label per code line allowed.")
      return res

  for idx, l in enumerate(lines):
    if idx + 1 < len(lines) and \
       l.find(':') != -1:
      label = l[0:-1]  # remove colon
      if label in labels:
        print("Error. Label %s already exist." % label)
      else:
        # use index of CLEARED code line because label will be removed from code
        labels[label] = len(res)
        label_of_line[len(res)] = label
    else:
      res.append(l)

  return res

def first(lines):
  for l in lines:
    p = l.split()
    if p[0] not in cmds:
      print("Error. Unknown cmd: " + p[0])
    if cmd_ok(p):
      parsed_cmd.append(p)
    else:
      have_errors = True
  return

def second():
  line_index = 0
  for c in parsed_cmd:
    if line_index in label_of_line:
      l = label_of_line[line_index]
      print(l, c)
    else:
      print(c)
    line_index += 1
  return

def asm(fname):
  print("Assembling: " + fname)
  if not os.path.isfile(fname):
    print("Error. File not exist.")
    return

  lines = read_and_prepare(fname)
  if len(lines) == 0:
    print("No useful code in file!")
    return

  lines = extract_labels(lines)
  for idx, l in enumerate(lines):
    if idx in label_of_line:
      print("%d: %s # %s" % (idx, l, label_of_line[idx]))
    else:
      print("%d: %s" % (idx, l))
  first(lines)

  for p in parsed_cmd:
    print(p)

def main():
  if len(sys.argv) != 2:
    print("To use type:\nasm.py your_source.asm\n")
    return
  asm(sys.argv[1])
  print("")
  print("labels: ", labels)
  print("label_of_line: ", label_of_line)

main()
