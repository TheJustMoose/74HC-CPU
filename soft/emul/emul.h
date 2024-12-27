/*
  74hcpu Emulator
*/

#pragma once

#include <cstdint>

#include "lcd.h"
#include "observer.h"

typedef uint16_t RAM_ADDR;
typedef uint8_t RAM_DATA;
constexpr RAM_ADDR LAST_RAM_ADDR {0xFFFF};

typedef uint16_t ROM_ADDR;
typedef uint16_t ROM_DATA;

typedef uint8_t PORT_DATA;

class Reg : public Subject {
public:
  Reg() = default;
  Reg(int v): value_(v) {}

  operator uint8_t() const {
    return value_;
  }

  operator int() const {
    return value_;
  }

  Reg& operator=(uint8_t v) {
    value_ = v;
    Notify();
    return *this;
  }

private:
  uint8_t value_ {0};
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

  void Step();

  void ActivateBank(int BankId);  // 0 - Bank0, 1 - Bank1

protected:
  Bank& ActiveBank();

private:
  ROM_ADDR IP{0};  // Instruction Pointer
  RAM_ADDR SP{LAST_RAM_ADDR};  // Stack Pointer

  int active_bank_num_ {0};
};

class System {
public:
  CPU cpu;
  LCD lcd;

  void Step();
};
