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
# example: NEG R1     | R1 := NEG R1
"CLR": {"COP": 8, "TP": 0, "ARGS": 1},
"INV": {"COP": 9, "TP": 0, "ARGS": 1},
"LSL": {"COP": 10, "TP": 0, "ARGS": 1},
"LSR": {"COP": 11, "TP": 0, "ARGS": 1},
"MIR": {"COP": 12, "TP": 0, "ARGS": 1},
"MOV": {"COP": 13, "TP": 0, "ARGS": 2},
"SWAB": {"COP": 14, "TP": 0, "ARGS": 1},
"SET": {"COP": 15, "TP": 0, "ARGS": 1},
# unary2 - same as unary, but we can use different SRC and DST
# example: NEG R2, R1     | R2 := NEG R1
# some pointless operations was removed
"INV2": {"COP": 9, "TP": 0, "ARGS": 2},
"LSL2": {"COP": 10, "TP": 0, "ARGS": 2},
"LSR2": {"COP": 11, "TP": 0, "ARGS": 2},
"MIR2": {"COP": 12, "TP": 0, "ARGS": 2},
"SWAB2": {"COP": 14, "TP": 0, "ARGS": 2},
# jump
"JZ": {"COP": 0, "TP": 1, "ARGS": 1},
"JNZ": {"COP": 1, "TP": 1, "ARGS": 1},
"JE": {"COP": 2, "TP": 1, "ARGS": 1},
"JNE": {"COP": 3, "TP": 1, "ARGS": 1},
"JG": {"COP": 4, "TP": 1, "ARGS": 1},
"JL": {"COP": 5, "TP": 1, "ARGS": 1},
"JC": {"COP": 6, "TP": 1, "ARGS": 1},
"JNC": {"COP": 7, "TP": 1, "ARGS": 1},
#"JS": {"COP": ?, "TP": 1, "ARGS": 1},
"JMP": {"COP": 8, "TP": 1, "ARGS": 1},
"CALL": {"COP": 9, "TP": 1, "ARGS": 1},
"RET": {"COP": 10, "TP": 1, "ARGS": 0},
"IRET": {"COP": 11, "TP": 1, "ARGS": 0},
"SIE": {"COP": 12, "TP": 1, "ARGS": 0},
"SIZ": {"COP": 13, "TP": 1, "ARGS": 0},
# control
"CLRF": {"COP": 0, "TP": 2, "ARGS": 0},
"NOP": {"COP": 1, "TP": 2, "ARGS": 0},
"DI": {"COP": 2, "TP": 2, "ARGS": 0},
"EI": {"COP": 3, "TP": 2, "ARGS": 0},
"RESET": {"COP": 4, "TP": 2, "ARGS": 0},
"BANK0": {"COP": 5, "TP": 2, "ARGS": 0},
"BANK1": {"COP": 6, "TP": 2, "ARGS": 0},
# transfer
"LOAD": {"COP": 0, "TP": 3, "ARGS": 1},
"STORE": {"COP": 1, "TP": 3, "ARGS": 1},
"IN": {"COP": 2, "TP": 3, "ARGS": 2},
"OUT": {"COP": 3, "TP": 3, "ARGS": 2},
"XOUT": {"COP": 4, "TP": 3, "ARGS": 2},
"CFG": {"COP": 5, "TP": 3, "ARGS": 2},
}

src_regs = {
"R0": 0,
"R1": 1,
"R2": 2,
"R3": 3,
"R4": 4,
"CONST": 5,
"PIN0": 6,
"PORT0": 7,
}

dst_regs = {
"R0": 0,
"R1": 1,
"R2": 2,
"R3": 3,
"R4": 4,
"R5": 5,
"R6": 6,
"R7": 7,
}

src_ports = {
"PIN0": 0,
"PIN1": 1,
"PIN2": 2,
"PIN3": 3,
"PIN4": 4,
"PIN5": 5,
"PIN6": 6,
"PIN7": 7,
}

dst_ports = {
"PORT0": 0,
"PORT1": 1,
"PORT2": 2,
"PORT3": 3,
"PORT4": 4,
"PORT5": 5,
"PORT6": 6,
"PORT7": 7,
}
