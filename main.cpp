// 6502 CPU Emulator

#include "opcodes.hpp"
#include <array>
#include <cstdint>
#include <cstdio>

using u8 = std::uint8_t;
using u16 = std::uint16_t;
const std::size_t RAM_SIZE = 64 * 1024;

// Helpers
u16 to16(u8 low, u8 high) { return (high << 8) | low; }

struct Bus {
  std::array<u8, RAM_SIZE> ram{};

  const u8 read(u16 addr) { return ram[addr]; }

  void write(u16 addr, u8 data) { ram[addr] = data; }
  // each memory address can only hold 8 bit data since 6502 is an 8 bit cpu
};

struct CPU {
  Bus bus;
  // Registers
  u16 PC{0x0000}; // program counter
  u8 SP{};        // stack pointer
  u8 A{0};        // accumulator
  u8 X{0};        // x register
  u8 Y{0};        // y register
  u8 cycles{0};   // cpu cycles

  // processor status
  struct Status {
    u8 CF : 1; // carry flag
    u8 ZF : 1; // zero flag
    u8 ID : 1; // interrupt disable
    u8 DM : 1; // decimal mode
    u8 BC : 1; // break command
    u8 OF : 1; // overflow flag
    u8 NF : 1; // negative flag
  };

  Status status;

  /*
  a = 10: 00000000 00001010
  b = 20: 00000000 00010100
  c = a << 8 : 00001010 00000000
  so now we combine it with b
  d = c | y
  c: 00001010 00000000
  b: 00000000 00010100
  d: 00001010 00010100

  and in the end the formula is
  x = (a << 8) | b
  shift by 8 bits to make space for b and then combine it with b
     */

  // Helpers
  void updateNZ(u8 value) {
    status.ZF = (value == 0);
    status.NF = (value & 0b10000000) > 0;
    // 0x80 = 10000000 - bits from right to left 0,7 (8 bits)
  }

  // Addressing modes
  // Immediate
  u16 IMM() {
    u16 temp = PC;
    PC++;
    return temp;
  }

  // Implied
  u16 IMP() { return 0; }

  // Zero Page
  u16 ZP() {
    u16 offset = bus.read(PC);
    PC++;
    return offset;
  }

  // Zero Page, X
  u16 ZPX() {}

  // Zero Page, Y
  u16 ZPY() {}

  // Relative
  u16 RL() {}

  // Absolute
  u16 ABS() {}

  // Absolute, X
  u16 ABSX() {}

  // Absolute, Y
  u16 ABSY() {}

  // Indirect
  u16 INDIRECT() {}

  // Indexed Indirect
  u16 IINDIRECT() {}

  // Instruction Handlers
  void LDA_IMM() {
    u16 addr = IMM();
    u8 byte = bus.read(addr);
    A = byte;
    updateNZ(A);
  }

  void LDA_ZP() {
    u16 addr = ZP();
    u8 byte = bus.read(addr);
    A = byte;
    updateNZ(byte);
  }

  void NOP() { return; }

  // Runtime
  void reset() {
    u8 low_byte = bus.read(0xFFFC);
    u8 high_byte = bus.read(0xFFFD);
    u16 addr = to16(low_byte, high_byte);
    PC = addr;
  }

  void LoadIntoRAM() {
    // implement this later, maybe even from a file
  }

  u8 fetch() {
    // read opcode byte from PC, increment PC by 1 byte because CPU is 8 bit,
    // and 8 bits = 1 byte
    u8 opcode = bus.read(PC);
    PC++;
    return opcode;
  }

  void decode_and_execute(u8 opcode) {
    switch (opcode) {
    case INS_LDA_IM:
      LDA_IMM();
      cycles = 2;
      break;
    case INS_NOP:
      NOP();
      cycles = 2;
      break;

    default:
      printf("Instruction not handled 0x%X", opcode);
      break;
    }
  }

  void step() {
    if (cycles == 0) {
      u8 opcode = fetch();
      decode_and_execute(opcode);
    }

    if (cycles > 0) {
      cycles--;
    }
  }
};

int main() {

  CPU cpu;

  // LDA instruction
  cpu.bus.write(0x8000, INS_LDA_IM); // Opcode 0xA9
  cpu.bus.write(0x8001, 0x42);       // Operand value 0x42

  // reset vector
  cpu.bus.write(0xFFFC, 0x00); // Low byte
  cpu.bus.write(0xFFFD, 0x80); // High byte

  cpu.reset();
  cpu.step();

  printf("Accumulator: 0x%X", cpu.A);

  return 0;
}
