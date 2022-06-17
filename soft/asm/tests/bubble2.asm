; array addr:
; F0 F1 F2 F3 F4 F5 F6 F7 F8 F9 FA FB FC FD FF
;  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15

; array end
mov r6, 0xFF
mov r7, 0xFF

rpt:
; array begin
mov r4, 0xF0
mov r5, 0xFF

clr r2 ; flag

sort_loop:
load [X], r0
rload [X+1], r1

cmp r0, r1
jl  skip_swap
; swap values
store [X], r1
rstore [X+1], r0
or   r2, 1  ; flag = 1
skip_swap:

inc  r4
incc r5

cmp  r4, r6 ; compare low byte
cmpc r5, r7 ; now compare high byte

jl   sort_loop

cmp  r2, 0
jne  rpt

out  port0, 1
stop
