/*
  74hcpu Emulator
*/

#pragma once

#include <cstdint>

typedef RAM_ADDR uint16_t;
typedef RAM_DATA uint8_t;
constexpr RAM_ADDR LAST_RAM_ADDR {0xFFFF};

typedef ROM_ADDR uint16_t;
typedef ROM_DATA uint16_t;

typedef PORT_DATA uint8_t;

class Reg {
public:
 uint8_t value {0};
};

class Bank {
  Reg R0;
  Reg R1;
  Reg R2;
  Reg R3;
  Reg R4;
  Reg R5;
  Reg R6;
  Reg R7;
};

class RAM {
public:
  RAM(uint8_t BitWidth);
};

class ROM {
public:
  ROM(ROM_ADDR max_addr)
    : max_addr_(max_addr) {}

  ROM_ADDR GetMaxAddress() {
    return max_addr_;
  }

  ROM_DATA Read(ROM_ADDR addr) {
    // вообще, ROM_ADDR 16 битный, поэтому проверка не имеет смысла (кажется)
    if (addr >= max_addr_)
      throw std::exception("ROM address out of bounds");
    return {};
  }

private:
  ROM_ADDR max_addr_;
};

class OutPort {
public:
  void Write(PORT_DATA);
};

class CPU {
private:
public:
  ROM rom;
  RAM ram;
  Bank bank0;
  Bank bank1;
  OutPort LCD_data;
  OutPort LCD_ctrl;
  OutPort port2;
  OutPort port3;

private:
  ROM_ADDR IP{0};  // Instruction Pointer
  RAM_ADDR SP{LAST_RAM_ADDR};  // Stack Pointer
};
