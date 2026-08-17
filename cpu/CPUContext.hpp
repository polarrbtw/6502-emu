#pragma once
#include "Bus.hpp"
#include "Registers.hpp"

struct CPUContext {
  Registers regs{};        // PC, SP, A, X, Y and flags
  Bus bus{};               // RAM and R/W functions
  u8 cycles{0};            // CPU cycles
  bool pageCrossed{false}; // Set by addressing modes when crossing a page
  bool branched{false};    // Set by branchIf helper (true if condition is true)
};
