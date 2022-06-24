  ; init RAM pointer
  set r7
  set r6
  set r5 ; -a
  ; fact(5)
  mov r3, 5
  call fact
  out port0, r0

stop:
  jmp stop

fact:  ; get param in r3, return result in r0
  cmp r3, 1     ; if param == 1
  jg  calc
  mov r0, 1     ;   return 1
  ret
calc:           ; else
  store r3      ;   t = param
  add r6, 0xFF  ; push
  addc r7, 0xFF

  add r3, 0xFF  ;   param--
  call fact     ; fact(param)

  add r6, 1
  addc r7, 0
  load r3       ; pop

  mul r0, r3    ; return param*fact() | r5:r4 := r4*r3
  ret
