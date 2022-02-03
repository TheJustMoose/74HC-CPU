; mul via add
; b  a
; r1:r0 - input params
; r5:r4 - result
; r7:r6 - ptr

mov r1, 100
mov r0, 100

clr r5 ; result
clr r4

clr r3 ; a
mov r2, r0

mov r7, 0xFF ; ptr
mov r6, 0xFF

loop:
mov r0, r1  ; t = b
and r0, 1   ; if (t & 1) // ZF = ?
siz ; skip next 2 command
add  r4, r2
addc r5, r3
clrf
lsl r2  ; a <<= 1
lsl r3
clrf
lsr r1  ; b >>= 1
jnz loop

ready:
store r5
add r6, 0xFF
addc r7, 0xFF
store r4
