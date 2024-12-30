/*
  74hcpu Emulator
*/

#pragma once

#include <cstdint>
#include <memory>

#include "lcd.h"
#include "observer.h"

typedef uint16_t RAM_ADDR;
typedef uint8_t RAM_DATA;
constexpr RAM_ADDR LAST_RAM_ADDR {0xFFFF};

typedef uint16_t ROM_ADDR;
typedef uint16_t ROM_DATA;

typedef uint8_t PORT_DATA;

class Instruction;

enum class Flags : uint8_t {
  CF = 0x01,
  ZF = 0x02,
  LF = 0x04,
  EF = 0x08,
  GF = 0x10,
  BF = 0x20,
  IF = 0x80
};

enum class Cops : uint8_t {
  ADD  = 0x00,
  ADDC = 0x10,
  AND  = 0x20,
  OR   = 0x30,
  XOR  = 0x40,
  MUL  = 0x50,
  UNO  = 0x60,
  MOV  = 0x70,
  LPM  = 0x80,
  LD   = 0x90,
  IN   = 0xA0,
  OUT  = 0xB0,
  ST   = 0xC0,
  CMP  = 0xD0,
  CMPC = 0xE0,
  CALL = 0xF0,
  BRANCH = CALL,
  JMP  = 0xF1,
  RET  = 0xF2,
  JZ   = 0xF3,
  JL   = 0xF4,
  JNE  = 0xF5,
  JE   = 0xF6,
  JG   = 0xF7,
  JC   = 0xF8,
  JNZ  = 0xF9,
  JNC  = 0xFA,
  JHC  = 0xFB,
  JNHC = 0xFC,
  STOP = 0xFD,
  AFCALL = 0xFE,
  NOP  = 0xFF,
};

std::unique_ptr<Instruction> CreateFromMachineCode(ROM_DATA machine_code);

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
  RAM(uint8_t BitWidth = 8) {}
};

class ROM {
public:
  ROM() = default;

  ROM_ADDR GetMaxAddress() {
    return max_addr_;
  }

  ROM_DATA Read(ROM_ADDR addr) {
    // вообще, ROM_ADDR 16 битный, поэтому проверка не имеет смысла (кажется)
    if (addr >= max_addr_)  // хотя если размер меньше 2^16, то лучше проверить :)
      throw std::exception("ROM address out of bounds");
    return rom_[addr];
  }

  void Flash(std::vector<ROM_DATA>&& rom) {
    if (rom.size() >= 0x10000)
      throw std::exception("Firmware is too large");

    rom_ = rom;
    max_addr_ = static_cast<ROM_ADDR>(rom_.size());
  }

private:
  ROM_ADDR max_addr_ {0};
  std::vector<ROM_DATA> rom_;
};

class OutPort {
public:
  void Write(PORT_DATA);
};

class CPU {
public:
  ROM rom;
  RAM ram;
  Bank bank0;
  Bank bank1;
  OutPort LCD_data;
  OutPort LCD_ctrl;
  OutPort port2;
  OutPort port3;
  Flags flags;

  CPU() {}

  void Step();

  void ActivateBank(int BankNum);  // 0 - Bank0, 1 - Bank1
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

class Instruction {
public:
  // 74hcpu has 16 bit instructions
  Instruction(ROM_DATA code) : code_(code) {}
  virtual void Execute(CPU* cpu) = 0;

protected:
  ROM_DATA code() {
    return code_;
  }

private:
  ROM_DATA code_ {0};
};

class BinaryInstruction : public Instruction {
public:
  BinaryInstruction(ROM_DATA code) : Instruction(code) {}

  virtual std::string Name() {
    return {};
  }

  uint8_t LeftOp(CPU*);
  uint8_t RightOp(CPU*);
};

class Add : public BinaryInstruction {
public:
  Add(ROM_DATA code) : BinaryInstruction(code) {}
  void Execute(CPU*) override;

  std::string Name() override { return "ADD"; }
};

class AddC : public BinaryInstruction {
public:
  AddC(ROM_DATA code) : BinaryInstruction(code) {}
  void Execute(CPU*) override;

  std::string Name() override { return "ADDC"; }
};

class And : public BinaryInstruction {
public:
  And(ROM_DATA code) : BinaryInstruction(code) {}
  void Execute(CPU*) override;

  std::string Name() override { return "AND"; }
};

class Or : public BinaryInstruction {
public:
  Or(ROM_DATA code) : BinaryInstruction(code) {}
  void Execute(CPU*) override;

  std::string Name() override { return "OR"; }
};

class Xor : public BinaryInstruction {
public:
  Xor(ROM_DATA code) : BinaryInstruction(code) {}
  void Execute(CPU*) override;

  std::string Name() override { return "XOR"; }
};

class Mul : public BinaryInstruction {
public:
  Mul(ROM_DATA code) : BinaryInstruction(code) {}
  void Execute(CPU*) override;

  std::string Name() override { return "MUL"; }
};

class Uno : public Instruction {
public:
  Uno(ROM_DATA code) : Instruction(code) {}
  void Execute(CPU*) override;
};

class Mov : public BinaryInstruction {
public:
  Mov(ROM_DATA code) : BinaryInstruction(code) {}
  void Execute(CPU*) override;

  std::string Name() override { return "MOV"; }
};

class Lpm : public Instruction {
public:
  Lpm(ROM_DATA code) : Instruction(code) {}
  void Execute(CPU*) override;
};

class Ld : public Instruction {
public:
  Ld(ROM_DATA code) : Instruction(code) {}
  void Execute(CPU*) override;
};

class In : public Instruction {
public:
  In(ROM_DATA code) : Instruction(code) {}
  void Execute(CPU*) override;
};

class Out : public Instruction {
public:
  Out(ROM_DATA code) : Instruction(code) {}
  void Execute(CPU*) override;
};

class St : public Instruction {
public:
  St(ROM_DATA code) : Instruction(code) {}
  void Execute(CPU*) override;
};

class Cmp : public BinaryInstruction {
public:
  Cmp(ROM_DATA code) : BinaryInstruction(code) {}
  void Execute(CPU*) override;

  std::string Name() override { return "CMP"; }
};

class CmpC : public BinaryInstruction {
public:
  CmpC(ROM_DATA code) : BinaryInstruction(code) {}
  void Execute(CPU*) override;

  std::string Name() override { return "CMPC"; }
};
