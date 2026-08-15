#pragma once
#include "Flags.hpp"

struct Registers {
  u16 PC{0x0000}; // program counter
  u8 SP{0x0000};  // stack pointer
  u8 A{0};        // accumulator
  u8 X{0};        // x register
  u8 Y{0};        // y register

  Flags flags{}; // processor status
};
