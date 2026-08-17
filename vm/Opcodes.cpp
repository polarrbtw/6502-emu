#include "Opcodes.hpp"
#include "../instructions/Instructions.hpp"
#include <algorithm>

/*
struct Opcode {
  addrFunc addrMode;
  instrFunc instr;
  u8 cycles;
  bool pageCross = false;
};
*/

namespace AM = AddressingModes;
namespace INS = Instructions;

// arr[0x00] = {AM:: , INS:: , };

const std::array<Opcode, 256> OpcodeTable = [] {
  std::array<Opcode, 256> arr{};
  std::fill(arr.begin(), arr.end(), Opcode{AM::IMM, INS::NOP, 2});

  // Load/Store
  arr[0xA9] = {AM::IMM, INS::LDA, 2};
  arr[0xA5] = {AM::ZP, INS::LDA, 3};
  arr[0xB5] = {AM::ZPX, INS::LDA, 4};
  arr[0xAD] = {AM::ABS, INS::LDA, 4};
  arr[0xBD] = {AM::ABSX, INS::LDA, 4, true};
  arr[0xB9] = {AM::ABSY, INS::LDA, 4, true};
  arr[0xA1] = {AM::IINDIRECTX, INS::LDA, 6};
  arr[0xB1] = {AM::IINDIRECTY, INS::LDA, 5, true};

  arr[0xA2] = {AM::IMM, INS::LDX, 2};
  arr[0xA6] = {AM::ZP, INS::LDX, 3};
  arr[0xB6] = {AM::ZPY, INS::LDX, 4};
  arr[0xAE] = {AM::ABS, INS::LDX, 4};
  arr[0xBE] = {AM::ABSY, INS::LDX, 4, true};

  arr[0xA0] = {AM::IMM, INS::LDY, 2};
  arr[0xA4] = {AM::ZP, INS::LDY, 3};
  arr[0xB4] = {AM::ZPX, INS::LDY, 4};
  arr[0xAC] = {AM::ABS, INS::LDY, 4};
  arr[0xBC] = {AM::ABSX, INS::LDY, 4, true};

  arr[0x85] = {AM::ZP, INS::STA, 3};
  arr[0x95] = {AM::ZPX, INS::STA, 4};
  arr[0x8D] = {AM::ABS, INS::STA, 4};
  arr[0x9D] = {AM::ABSX, INS::STA, 5};
  arr[0x99] = {AM::ABSY, INS::STA, 5};
  arr[0x81] = {AM::IINDIRECTX, INS::STA, 6};
  arr[0x91] = {AM::IINDIRECTY, INS::STA, 6};

  arr[0x86] = {AM::ZP, INS::STX, 3};
  arr[0x96] = {AM::ZPY, INS::STX, 4};
  arr[0x8E] = {AM::ABS, INS::STX, 4};

  arr[0x84] = {AM::ZP, INS::STY, 3};
  arr[0x94] = {AM::ZPX, INS::STY, 4};
  arr[0x8C] = {AM::ABS, INS::STY, 4};

  // Register Transfers
  arr[0xAA] = {AM::IMP, INS::TAX, 2};
  arr[0xA8] = {AM::IMP, INS::TAY, 2};
  arr[0x8A] = {AM::IMP, INS::TXA, 2};
  arr[0x98] = {AM::IMP, INS::TYA, 2};

  // Stack Operations
  arr[0xBA] = {AM::IMP, INS::TSX, 2};
  arr[0x9A] = {AM::IMP, INS::TXS, 2};
  arr[0x48] = {AM::IMP, INS::PHA, 3};
  arr[0x08] = {AM::IMP, INS::PHP, 3};
  arr[0x68] = {AM::IMP, INS::PLA, 4};
  arr[0x28] = {AM::IMP, INS::PLP, 4};

  // Logical
  arr[0x29] = {AM::IMM, INS::AND, 2};
  arr[0x25] = {AM::ZP, INS::AND, 3};
  arr[0x35] = {AM::ZPX, INS::AND, 4};
  arr[0x2D] = {AM::ABS, INS::AND, 4};
  arr[0x3D] = {AM::ABSX, INS::AND, 4, true};
  arr[0x39] = {AM::ABSY, INS::AND, 4, true};
  arr[0x21] = {AM::IINDIRECTX, INS::AND, 6};
  arr[0x31] = {AM::IINDIRECTY, INS::AND, 5, true};
  arr[0x49] = {AM::IMM, INS::EOR, 2};
  arr[0x45] = {AM::ZP, INS::EOR, 3};
  arr[0x55] = {AM::ZPX, INS::EOR, 4};
  arr[0x4D] = {AM::ABS, INS::EOR, 4};
  arr[0x5D] = {AM::ABSX, INS::EOR, 4, true};
  arr[0x59] = {AM::ABSY, INS::EOR, 4, true};
  arr[0x41] = {AM::IINDIRECTX, INS::EOR, 6};
  arr[0x51] = {AM::IINDIRECTY, INS::EOR, 5, true};
  arr[0x09] = {AM::IMM, INS::ORA, 2};
  arr[0x05] = {AM::ZP, INS::ORA, 3};
  arr[0x15] = {AM::ZPX, INS::ORA, 4};
  arr[0x0D] = {AM::ABS, INS::ORA, 4};
  arr[0x1D] = {AM::ABSX, INS::ORA, 4, true};
  arr[0x19] = {AM::ABSY, INS::ORA, 4, true};
  arr[0x01] = {AM::IINDIRECTX, INS::ORA, 6};
  arr[0x11] = {AM::IINDIRECTY, INS::ORA, 5, true};
  arr[0x24] = {AM::ZP, INS::BIT, 3};
  arr[0x2C] = {AM::ABS, INS::BIT, 4};

  // Arithmetic
  arr[0x69] = {AM::IMM, INS::ADC, 2};
  arr[0x65] = {AM::ZP, INS::ADC, 3};
  arr[0x75] = {AM::ZPX, INS::ADC, 4};
  arr[0x6D] = {AM::ABS, INS::ADC, 4};
  arr[0x7D] = {AM::ABSX, INS::ADC, 4, true};
  arr[0x79] = {AM::ABSY, INS::ADC, 4, true};
  arr[0x61] = {AM::IINDIRECTX, INS::ADC, 6};
  arr[0x71] = {AM::IINDIRECTY, INS::ADC, 5, true};
  arr[0xE9] = {AM::IMM, INS::SBC, 2};
  arr[0xE5] = {AM::ZP, INS::SBC, 3};
  arr[0xF5] = {AM::ZPX, INS::SBC, 4};
  arr[0xED] = {AM::ABS, INS::SBC, 4};
  arr[0xFD] = {AM::ABSX, INS::SBC, 4, true};
  arr[0xF9] = {AM::ABSY, INS::SBC, 4, true};
  arr[0xE1] = {AM::IINDIRECTX, INS::SBC, 6};
  arr[0xF1] = {AM::IINDIRECTY, INS::SBC, 5, true};
  arr[0xC9] = {AM::IMM, INS::CMP, 2};
  arr[0xC5] = {AM::ZP, INS::CMP, 3};
  arr[0xD5] = {AM::ZPX, INS::CMP, 4};
  arr[0xCD] = {AM::ABS, INS::CMP, 4};
  arr[0xDD] = {AM::ABSX, INS::CMP, 4, true};
  arr[0xD9] = {AM::ABSY, INS::CMP, 4, true};
  arr[0xC1] = {AM::IINDIRECTX, INS::CMP, 6};
  arr[0xD1] = {AM::IINDIRECTY, INS::CMP, 5, true};
  arr[0xE0] = {AM::IMM, INS::CPX, 2};
  arr[0xE4] = {AM::ZP, INS::CPX, 3};
  arr[0xEC] = {AM::ABS, INS::CPX, 4};
  arr[0xC0] = {AM::IMM, INS::CPY, 2};
  arr[0xC4] = {AM::ZP, INS::CPY, 3};
  arr[0xCC] = {AM::ABS, INS::CPY, 4};

  // Increments & Decrements
  arr[0xE6] = {AM::ZP, INS::INC, 5};
  arr[0xF6] = {AM::ZPX, INS::INC, 6};
  arr[0xEE] = {AM::ABS, INS::INC, 6};
  arr[0xFE] = {AM::ABSX, INS::INC, 7};
  arr[0xE8] = {AM::IMP, INS::INX, 2};
  arr[0xC8] = {AM::IMP, INS::INY, 2};
  arr[0xC6] = {AM::ZP, INS::DEC, 5};
  arr[0xD6] = {AM::ZPX, INS::DEC, 6};
  arr[0xCE] = {AM::ABS, INS::DEC, 6};
  arr[0xDE] = {AM::ABSX, INS::DEC, 7};
  arr[0xCA] = {AM::IMP, INS::DEX, 2};
  arr[0x88] = {AM::IMP, INS::DEY, 2};

  // Shifts
  arr[0x0A] = {AM::IMP, INS::ASL, 2};
  arr[0x06] = {AM::ZP, INS::ASL, 5};
  arr[0x16] = {AM::ZPX, INS::ASL, 6};
  arr[0x0E] = {AM::ABS, INS::ASL, 6};
  arr[0x1E] = {AM::ABSX, INS::ASL, 7};
  arr[0x4A] = {AM::IMP, INS::LSR, 2};
  arr[0x46] = {AM::ZP, INS::LSR, 5};
  arr[0x56] = {AM::ZPX, INS::LSR, 6};
  arr[0x4E] = {AM::ABS, INS::LSR, 6};
  arr[0x5E] = {AM::ABSX, INS::LSR, 7};
  arr[0x2A] = {AM::IMP, INS::ROL, 2};
  arr[0x26] = {AM::ZP, INS::ROL, 5};
  arr[0x36] = {AM::ZPX, INS::ROL, 6};
  arr[0x2E] = {AM::ABS, INS::ROL, 6};
  arr[0x3E] = {AM::ABSX, INS::ROL, 7};
  arr[0x6A] = {AM::IMP, INS::ROR, 2};
  arr[0x66] = {AM::ZP, INS::ROR, 5};
  arr[0x76] = {AM::ZPX, INS::ROR, 6};
  arr[0x6E] = {AM::ABS, INS::ROR, 6};
  arr[0x7E] = {AM::ABSX, INS::ROR, 7};

  // Jumps & Calls
  arr[0x4C] = {AM::ABS, INS::JMP, 3};
  arr[0x6C] = {AM::INDIRECT, INS::JMP, 5};
  arr[0x20] = {AM::ABS, INS::JSR, 6};
  arr[0x60] = {AM::IMP, INS::RTS, 6};

  // Branches
  arr[0x90] = {AM::RL, INS::BCC, 2, true};
  arr[0xB0] = {AM::RL, INS::BCS, 2, true};
  arr[0xF0] = {AM::RL, INS::BEQ, 2, true};
  arr[0x30] = {AM::RL, INS::BMI, 2, true};
  arr[0xD0] = {AM::RL, INS::BNE, 2, true};
  arr[0x10] = {AM::RL, INS::BPL, 2, true};
  arr[0x50] = {AM::RL, INS::BVC, 2, true};
  arr[0x70] = {AM::RL, INS::BVS, 2, true};

  // Status Flag Changes
  arr[0x18] = {AM::IMP, INS::CLC, 2};
  arr[0xD8] = {AM::IMP, INS::CLD, 2};
  arr[0x58] = {AM::IMP, INS::CLI, 2};
  arr[0xB8] = {AM::IMP, INS::CLV, 2};
  arr[0x38] = {AM::IMP, INS::SEC, 2};
  arr[0xF8] = {AM::IMP, INS::SED, 2};
  arr[0x78] = {AM::IMP, INS::SEI, 2};

  // System Functions
  arr[0x00] = {AM::IMP, INS::BRK, 7};
  arr[0xEA] = {AM::IMP, INS::NOP, 2};
  arr[0x40] = {AM::IMP, INS::RTI, 6};

  return arr;
}();
