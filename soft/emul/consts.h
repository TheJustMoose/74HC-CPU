#pragma once

#include <cstdint>

enum class Flags : uint8_t {
  CF = 0x01,  // carry
  ZF = 0x02,  // zero
  LF = 0x04,  // less than
  EF = 0x08,  // equal
  GF = 0x10,  // great than
  BF = 0x20,  // bank flag
  IF = 0x80   // interrupt flag
};

enum class Cops : uint8_t {
  cADD  = 0x00,
  cADDC = 0x10,
  cAND  = 0x20,
  cOR   = 0x30,
  cXOR  = 0x40,
  cMUL  = 0x50,
  cUNO  = 0x60,
  cMOV  = 0x70,
  cLPM  = 0x80,
  cLD   = 0x90,
  cIN   = 0xA0,
  cOUT  = 0xB0,
  cST   = 0xC0,
  cCMP  = 0xD0,
  cCMPC = 0xE0,
  cCALL = 0xF0,
  cBRANCH = cCALL,
  cJMP  = 0xF1,
  cRET  = 0xF2,
  cJZ   = 0xF3,
  cJL   = 0xF4,
  cJNE  = 0xF5,
  cJE   = 0xF6,
  cJG   = 0xF7,
  cJC   = 0xF8,
  cJNZ  = 0xF9,
  cJNC  = 0xFA,
  cJHC  = 0xFB,
  cJNHC = 0xFC,
  cSTOP = 0xFD,
  cAFCALL = 0xFE,
  cNOP  = 0xFF
};

struct BIN_INS_FLAGS {
  // LSB
  uint8_t i : 1;    // invert lo nibble
  uint8_t I : 1;    // invert hi nibble
  uint8_t z : 1;    // zero lo nibble
  uint8_t Z : 1;    // zero hi nibble
  uint8_t frc : 1;  // force to set CF flag
  uint8_t src : 3;  // source register
  // MSB
};

union BIN_INS_LOW_BYTE {
  BIN_INS_FLAGS Flags;
  uint8_t Const;
};

struct BIN_INS_HIGH_BYTE {
  // LSB
  uint8_t cnst : 1;      // const or register
  uint8_t dst : 3;       // destination register
  uint8_t cop : 4;       // code of operation
  // MSB
};

struct BIN_INS {
  // low byte:
  BIN_INS_LOW_BYTE low;  // can contain flags or const
  // high byte:
  BIN_INS_HIGH_BYTE high;  // COP, etc
};

union INSTRUCTION {
  uint16_t machine_code;
  uint8_t bytes[2];
  BIN_INS bin_ins;
};
