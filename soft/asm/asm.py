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

labels = []
label_of_line = {}
parsed_cmd = []
have_errors = False

def cmd_ok(parts):
  name = parts[0].upper()
  cmd = cmds[name]
  args = cmd["ARGS"]
  if len(parts) - 1 != args:
    print("Wait for %d args in %s" % (args, name))
    return False
  return True

def first(fname):
  print("Assembling: " + fname)
  if os.path.isfile(fname):
    with open(fname) as f:
      lines = f.readlines()
      last_label = ""
      for l in lines:
        pos = l.find(';')
        if pos != -1:  # remove comments
          l = l[:pos]
        l = l.strip()  # remove spaces
        pos = l.find(':')
        if pos != -1:
          label = l[:pos]
          l = l[pos+1:]
          print(label)
          if len(label) > 0:
            labels.append(label)
            last_label = label
        p = l.split()  # get command parts
        if len(p) == 0:
          continue
        if p[0].upper() not in cmds:
          print("Unknown cmd: " + p[0])
        if cmd_ok(p):
          parsed_cmd.append(p)
          if len(last_label) > 0:
            label_of_line[len(parsed_cmd)-1] = last_label
            last_label = ""
        else:
          have_errors = True
  else:
    print("File not exist")
    #with 
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
  first(fname)
  second()
  #print(parsed_cmd)

def main():
  if len(sys.argv) != 2:
    print("To use type:\nasm.py your_source.asm\n")
    return
  asm(sys.argv[1])
  print("labels: ", labels)

main()
