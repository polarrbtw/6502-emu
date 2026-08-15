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

// Instructions

// Load/Store Operations
inline void LDA(CPUContext &ctx, u16 addr) { loadReg(ctx, ctx.regs.A, addr); }

inline void LDX(CPUContext &ctx, u16 addr) { loadReg(ctx, ctx.regs.X, addr); }

inline void LDY(CPUContext &ctx, u16 addr) { loadReg(ctx, ctx.regs.Y, addr); }

inline void STA(CPUContext &ctx, u16 addr) { storeReg(ctx, ctx.regs.A, addr); }

inline void STX(CPUContext &ctx, u16 addr) { storeReg(ctx, ctx.regs.X, addr); }

inline void STY(CPUContext &ctx, u16 addr) { storeReg(ctx, ctx.regs.Y, addr); }

// Register Transfers
inline void TAX(CPUContext &ctx, u16 addr) {
  ctx.regs.X = ctx.regs.A;
  ctx.regs.flags.updateNZ(ctx.regs.X);
}

inline void TAY(CPUContext &ctx, u16 addr) {
  ctx.regs.Y = ctx.regs.A;
  ctx.regs.flags.updateNZ(ctx.regs.Y);
}

inline void TXA(CPUContext &ctx, u16 addr) {
  ctx.regs.A = ctx.regs.X;
  ctx.regs.flags.updateNZ(ctx.regs.A);
}

inline void TYA(CPUContext &ctx, u16 addr) {
  ctx.regs.A = ctx.regs.Y;
  ctx.regs.flags.updateNZ(ctx.regs.A);
}

// Stack Operations
inline void TSX(CPUContext &ctx, u16 addr) {}

inline void TXS(CPUContext &ctx, u16 addr) {}

inline void PHA(CPUContext &ctx, u16 addr) {}

inline void PHP(CPUContext &ctx, u16 addr) {}

inline void PLA(CPUContext &ctx, u16 addr) {}

inline void PLP(CPUContext &ctx, u16 addr) {}

// Logical

inline void AND(CPUContext &ctx, u16 addr) {}

inline void EOR(CPUContext &ctx, u16 addr) {}

inline void ORA(CPUContext &ctx, u16 addr) {}

inline void BIT(CPUContext &ctx, u16 addr) {}

// Arithmetic

inline void ADC(CPUContext &ctx, u16 addr) {}

inline void SBC(CPUContext &ctx, u16 addr) {}

inline void CMP(CPUContext &ctx, u16 addr) {}

inline void CMX(CPUContext &ctx, u16 addr) {}

inline void CPY(CPUContext &ctx, u16 addr) {}

// Shifts

inline void ASL(CPUContext &ctx, u16 addr) {}

inline void LSR(CPUContext &ctx, u16 addr) {}

inline void ROL(CPUContext &ctx, u16 addr) {}

inline void ROR(CPUContext &ctx, u16 addr) {}

// Jumps & Calls

inline void JMP(CPUContext &ctx, u16 addr) {}

inline void JSR(CPUContext &ctx, u16 addr) {}

inline void RTS(CPUContext &ctx, u16 addr) {}

// Branches

inline void BCC(CPUContext &ctx, u16 addr) {}

inline void BCS(CPUContext &ctx, u16 addr) {}

inline void BEQ(CPUContext &ctx, u16 addr) {}

inline void BMI(CPUContext &ctx, u16 addr) {}

inline void BNE(CPUContext &ctx, u16 addr) {}

inline void BPL(CPUContext &ctx, u16 addr) {}

inline void BVC(CPUContext &ctx, u16 addr) {}

inline void BVS(CPUContext &ctx, u16 addr) {}

// Status Flag Changes

inline void CLC(CPUContext &ctx, u16 addr) {}

inline void CLD(CPUContext &ctx, u16 addr) {}

inline void CLI(CPUContext &ctx, u16 addr) {}

inline void CLV(CPUContext &ctx, u16 addr) {}

inline void SEC(CPUContext &ctx, u16 addr) {}

inline void SED(CPUContext &ctx, u16 addr) {}

inline void SEI(CPUContext &ctx, u16 addr) {}

// System Functions
inline void BRK(CPUContext &ctx, u16 addr) {}

inline void NOP(CPUContext &ctx, u16 addr) {}

inline void RTI(CPUContext &ctx, u16 addr) {}

} // namespace Instructions
