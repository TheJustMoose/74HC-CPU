
  mov r0, 1

loop:
  add r0, 1
  cmp r0, 5
  sie
  jmp loop
  nop
