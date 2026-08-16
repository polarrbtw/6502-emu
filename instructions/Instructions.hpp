#pragma once
#include "../cpu/CPUContext.hpp"
#include "../instructions/AddressingModes.hpp"

namespace Instructions {

// Helpers
inline void loadReg(CPUContext &ctx, u8 &reg, u16 addr) {
  reg = ctx.bus.read(addr);
  ctx.regs.flags.updateNZ(reg);
}

inline void storeReg(CPUContext &ctx, u8 reg, u16 addr) {
  ctx.bus.write(addr, reg);
}

inline void compareReg(CPUContext &ctx, u8 reg, u8 data) {
  // for CMP instructions
  u8 result = reg - data;
  ctx.regs.flags.CF = reg >= data;
  ctx.regs.flags.ZF = reg == data;

  ctx.regs.flags.NF = (result & 0b10000000) > 0;
}

// Stack
inline void push8(CPUContext &ctx, u8 val) {
  u16 addr = static_cast<u16>(0x100 + ctx.regs.SP);
  ctx.bus.write(addr, val);
  ctx.regs.SP--;
}

inline void push16(CPUContext &ctx, u16 val) {
  u8 low = val;
  u8 high = val >> 8;
  push8(ctx, high);
  push8(ctx, low);
}

inline u8 pop8(CPUContext &ctx) {
  ctx.regs.SP++;
  u16 addr = static_cast<u16>(0x100 + ctx.regs.SP);
  return ctx.bus.read(addr);
}

inline u16 pop16(CPUContext &ctx) {
  // ctx.regs.SP++; // pop8 already increments stack, we would increment thrice
  // instead of twice
  u8 low = pop8(ctx);
  u8 high = pop8(ctx);
  return ctx.bus.to16(low, high);
}

// Instructions

// Load/Store Operations
void LDA(CPUContext &ctx, u16 addr);
void LDX(CPUContext &ctx, u16 addr);
void LDY(CPUContext &ctx, u16 addr);

void STA(CPUContext &ctx, u16 addr);
void STX(CPUContext &ctx, u16 addr);
void STY(CPUContext &ctx, u16 addr);

// Register Transfers
void TAX(CPUContext &ctx, u16 addr);
void TXA(CPUContext &ctx, u16 addr);

void TAY(CPUContext &ctx, u16 addr);
void TYA(CPUContext &ctx, u16 addr);

// Stack Operations
void TSX(CPUContext &ctx, u16 addr);
void TXS(CPUContext &ctx, u16 addr);

void PHA(CPUContext &ctx, u16 addr);
void PHP(CPUContext &ctx, u16 addr);

void PLA(CPUContext &ctx, u16 addr);
void PLP(CPUContext &ctx, u16 addr);

// Logical

void AND(CPUContext &ctx, u16 addr);
void EOR(CPUContext &ctx, u16 addr);
void ORA(CPUContext &ctx, u16 addr);
void BIT(CPUContext &ctx, u16 addr);

// Arithmetic

void ADC(CPUContext &ctx, u16 addr);
void SBC(CPUContext &ctx, u16 addr);

void CMP(CPUContext &ctx, u16 addr);
void CPX(CPUContext &ctx, u16 addr);
void CPY(CPUContext &ctx, u16 addr);

// Increments/Decrements
void INC(CPUContext &ctx, u16 addr);
void INX(CPUContext &ctx, u16 addr);
void INY(CPUContext &ctx, u16 addr);

void DEC(CPUContext &ctx, u16 addr);
void DEX(CPUContext &ctx, u16 addr);
void DEY(CPUContext &ctx, u16 addr);

// Shifts

void ASL(CPUContext &ctx, u16 addr);
void LSR(CPUContext &ctx, u16 addr);

void ROL(CPUContext &ctx, u16 addr);
void ROR(CPUContext &ctx, u16 addr);

// Jumps & Calls

void JMP(CPUContext &ctx, u16 addr);
void JSR(CPUContext &ctx, u16 addr);
void RTS(CPUContext &ctx, u16 addr);

// Branches

void BCC(CPUContext &ctx, u16 addr);
void BCS(CPUContext &ctx, u16 addr);

void BEQ(CPUContext &ctx, u16 addr);
void BMI(CPUContext &ctx, u16 addr);

void BNE(CPUContext &ctx, u16 addr);
void BPL(CPUContext &ctx, u16 addr);

void BVC(CPUContext &ctx, u16 addr);
void BVS(CPUContext &ctx, u16 addr);

// Status Flag Changes

void CLC(CPUContext &ctx, u16 addr);
void CLD(CPUContext &ctx, u16 addr);
void CLI(CPUContext &ctx, u16 addr);
void CLV(CPUContext &ctx, u16 addr);

void SEC(CPUContext &ctx, u16 addr);
void SED(CPUContext &ctx, u16 addr);
void SEI(CPUContext &ctx, u16 addr);

// System Functions
void BRK(CPUContext &ctx, u16 addr);
void NOP(CPUContext &ctx, u16 addr);
void RTI(CPUContext &ctx, u16 addr);

} // namespace Instructions
