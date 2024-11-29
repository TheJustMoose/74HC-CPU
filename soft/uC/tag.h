#pragma once

enum class Tag {
  tEMPTY = 0,
  tLess  = '<',  tMore   = '>',
  tSEMI  = ';',  tLBRACE = '{',
  tAND   = 256,  tBASIC = 257,  tBREAK = 258,  tDO   = 259, tELSE  = 260,
  tEQ    = 261,  tFALSE = 262,  tGE    = 263,  tID   = 264, tIF    = 265,
  tINDEX = 266,  tLE    = 267,  tMINUS = 268,  tNE   = 269, tNUM   = 270,
  tOR    = 271,  tREAL  = 272,  tTEMP  = 273,  tTRUE = 274, tWHILE = 275
};
