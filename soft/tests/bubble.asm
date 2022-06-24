
; r0 - value 1
; r1 - value 2
; r2 - pass counter
; r3 - repeat flag
; r7:r6 (bank0) - ptr0
; r7:r6 (bank1) - ptr1

bank0
mov r2, 16   ; pass counter

pass:
bank0
mov r6, 0xF1 ; ptr0
mov r7, 0xFF
bank1
mov r6, 0xF0 ; ptr1
mov r7, 0xFF

clr r3 ; flag

loop:
bank0
load r0

bank1
load r1

cmp r0, r1
jg skip
set r3   ; flag := 1
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

cmp r3, 0 ; no one swap happened
je stop

bank0
add r2, 0xFF
jnz pass

stop:
nop
nop
