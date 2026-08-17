#include "Instructions.hpp"

namespace Instructions {

// CLC - Clear carry flag
void CLC(CPUContext &ctx, u16 addr) { ctx.regs.flags.CF = 0; }

// CLD - Clear decimal mode flag
void CLD(CPUContext &ctx, u16 addr) { ctx.regs.flags.DM = 0; }

// CLI - Clear interrupt disable flag
void CLI(CPUContext &ctx, u16 addr) { ctx.regs.flags.ID = 0; }

// CLV - Clear overflow flag
void CLV(CPUContext &ctx, u16 addr) { ctx.regs.flags.OF = 0; }

// SEC - Set carry flag
void SEC(CPUContext &ctx, u16 addr) { ctx.regs.flags.CF = 1; }

// SED - Set decimal mode flag
void SED(CPUContext &ctx, u16 addr) { ctx.regs.flags.DM = 1; }

// SEI - Set interrupt disable flag
void SEI(CPUContext &ctx, u16 addr) { ctx.regs.flags.ID = 1; }

} // namespace Instructions
