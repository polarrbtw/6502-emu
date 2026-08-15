#include <cstdint>

using u8 = std::uint8_t;
using u16 = std::uint16_t;

// LDA
static constexpr u8 INS_LDA_IM = 0xA9;
static constexpr u8 INS_LDA_ZP = 0xA5;
static constexpr u8 INS_LDA_ZPX = 0xB5;
static constexpr u8 INS_LDA_A = 0xAD;
static constexpr u8 INS_LDA_AX = 0xAD;
static constexpr u8 INS_LDA_AY = 0xB9;
static constexpr u8 INS_LDA_IX = 0xA1;
static constexpr u8 INS_LDA_IY = 0xB1;

// LDX

// Other
static constexpr u8 INS_NOP = 0xEA;
