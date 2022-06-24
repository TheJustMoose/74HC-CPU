and r2, r3
and r3, 0
or r5, r3
or r5, 55
xor r7, r2
xor r5, 55

m1:
add r6, r0
addc r7, r1

add r2, 33
addc r3, 33
jmp m1

mul r2, 133
mul r2, r3

cmp r6, 255
cmpc r7, 255

jl m1
jmp 100
f1:
clr r1
inv r2
;neg r2, 10
lsl r0
lsr r1
mir r2
mov r7, r1
swab r3
set r0
ret

i1:
iret

jz m1
jnz m1

je m1
jg m1
jl m1

jc m1
jnc m1

js m1

jmp m1
call f1
call 0xFFF
ret
iret
sie

clrf
nop
di
ei
reset

load r4
store r3 ; we can write into memory only regs
in r0, pin0
out port1, r1
xout port7, 10

cfg 1000, r1
