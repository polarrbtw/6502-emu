#include "../cpu/CPUContext.hpp"
#include "Opcodes.hpp"

class VM {
public:
  CPUContext ctx;

  void Reset();
  void LoadIntoRom(); // todo
  void Step();

private:
  u8 Fetch();
  void Execute(u8 opcode);
};

inline void VM::Reset() {
  u16 addr = ctx.bus.readWord(0xFFFC);
  ctx.regs.PC = addr;
  ctx.regs.SP = 0xFF;
}

inline u8 VM::Fetch() {
  u8 opcode = ctx.bus.read(ctx.regs.PC);
  ctx.regs.PC++;
  return opcode;
}

inline void VM::Execute(u8 opcode) {
  Opcode op = OpcodeTable[opcode];

  // reset these every time
  ctx.pageCrossed = false;
  ctx.branched = false;

  u16 addr = op.addrMode(ctx);
  op.instr(ctx, addr);

  // special cases if we need to add extra cycles
  u8 extraCycles = op.cycles;
  if (op.pageCross && ctx.pageCrossed) {
    extraCycles++;
  }

  // branch instructions
  if (ctx.branched) {
    extraCycles++;
    if (ctx.pageCrossed)
      extraCycles++;
  }

  ctx.cycles += extraCycles;
}

inline void VM::Step() {
  if (ctx.cycles == 0) {
    u8 opcode = Fetch();
    Execute(opcode);
  }

  if (ctx.cycles > 0) {
    ctx.cycles--;
  }
}
