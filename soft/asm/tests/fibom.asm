; Test code for 74HCPU
; Fibonacci
; v = 1
; p = 0
; while (1):
;   t = v
;   v = v + p
;   p = t
;   print(v)

.def v=r1
.def p=r0
.def t=r2

  call fibo
in:
  jmp in

fibo:
  mov v, 1     ; v
  clr p        ; p
m1:
  mov t, v     ; t = v
  add v, p     ; v += p (модифицирует флаг CF)
  mov p, t     ; p = t
  out PORT0, v ; print(v)
  jnc  m1      ; while (v < 255)
  ret
