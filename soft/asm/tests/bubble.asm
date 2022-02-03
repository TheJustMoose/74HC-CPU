
bank0
mov r2, 16   ; pass counter

pass:
bank0
mov r6, 0xF1 ; ptr0
mov r7, 0xFF
bank1
mov r6, 0xF0 ; ptr1
mov r7, 0xFF

loop:
bank0
load r0

bank1
load r1

cmp r0, r1
jl skip
store r0 ; into ptr1
bank0
store r1 ; into ptr0

skip:
bank0
add r6, 1
addc r7, 0
bank1
add r6, 1
addc r7, 0

cmp r6, 0xFF
jl loop

bank0
add r2, 0xFF
jnz pass

nop
nop
