#pragma once
#include "Types.hpp"
#include <array>

const std::size_t RAM_SIZE = 64 * 1024;

struct Bus {
  std::array<u8, RAM_SIZE> ram{};

  u8 read(u16 addr) const { return ram[addr]; }

  void write(u16 addr, u8 data) { ram[addr] = data; }

  u16 to16(u8 low, u8 high) const { return (high << 8) | low; }
  // each 16 memory address can only hold 8 bit data since 6502 is an 8 bit cpu

  // read 2 bytes/operands after opcode
  u8 readWord(u16 addr) const {
    u16 temp = addr;
    return to16(read(addr), read(temp++));
  }
};
