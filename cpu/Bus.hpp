#pragma once
#include "Types.hpp"
#include <array>

const std::size_t RAM_SIZE = 64 * 1024;

struct Bus {
  std::array<u8, RAM_SIZE> ram{};

  u8 read(u16 addr) const { return ram[addr]; }

  // read 2 bytes
  u16 readWord(u16 addr) const {
    u16 temp = addr;
    temp += 1;
    return to16(read(addr), read(temp));
  }

  void write(u16 addr, u8 data) { ram[addr] = data; }

  // write 2 bytes
  void writeWord(u16 addr, u16 data) {
    u8 low = data;
    u8 high = data >> 8;
    ram[addr] = low;
    ram[addr + 1] = high;
  }

  u16 to16(u8 low, u8 high) const { return (high << 8) | low; }
  // each 16 memory address can only hold 8 bit data since 6502 is an 8 bit cpu
};
