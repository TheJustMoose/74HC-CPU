; Test code for 74HCPU
; Fibonacci
; v = 1
; p = 0
; while (1):
;   t = v
;   v = v + p
;   p = t
;   print(v)

  call fibo
in:
  jmp in

fibo:
  mov r1, 1     ; v
  clr r0        ; p
m1:
  mov r2, r1    ; t = v
  add r1, r0    ; v += p (модифицирует флаг CF)
  mov r0, r2    ; p = t
  out PORT0, r1 ; print(v)
  jnc  m1       ; while (v < 255)
  ret
