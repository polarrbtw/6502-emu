#include "Instructions.hpp"

namespace Instructions {

    void TAX(CPUContext &ctx, u16 addr) {
        ctx.regs.X = ctx.regs.A;
        ctx.regs.flags.updateNZ(ctx.regs.X);
    }

    void TAY(CPUContext &ctx, u16 addr) {
        ctx.regs.Y = ctx.regs.A;
        ctx.regs.flags.updateNZ(ctx.regs.Y);
    }

    void TXA(CPUContext &ctx, u16 addr) {
        ctx.regs.A = ctx.regs.X;
        ctx.regs.flags.updateNZ(ctx.regs.A);
    }

    void TYA(CPUContext &ctx, u16 addr) {
        ctx.regs.A = ctx.regs.Y;
        ctx.regs.flags.updateNZ(ctx.regs.A);
    }


}
