#include "../cpu/CPUContext.hpp"
#include "Opcodes.hpp"
#include <fstream>
#include <iostream>

#define ok(msg, ...) printf("[VM ] " msg "\n", ##__VA_ARGS__)
#define dbg(msg, ...) printf("[VM Debug] " msg "\n", ##__VA_ARGS__)
#define error(msg, ...) printf("[VM Error] " msg "\n", ##__VA_ARGS__)

class VM {
public:
  CPUContext ctx;

  void Reset();
  void LoadROM(const char *data, u16 base);
  void Step();
  void dbgState(u8 opcode);

private:
  u8 Fetch();
  void Execute(u8 opcode);
};

inline void VM::Reset() {
  ok("reset sequence");
  u16 resetVector = ctx.bus.readWord(0xFFFC);
  ctx.regs.PC = resetVector;
  ctx.regs.SP = 0xFF;

  ctx.cycles = 7; // apparently takes 7 cycles to do reset
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
    Execute(Fetch());
    ctx.cycles--; // cycle spent fetching
  } else {
    ctx.cycles--;
  }
}

inline void VM::LoadROM(const char *data, u16 base) {
  using namespace std; // scoped anyways
  ifstream ROM(data, std::ios::binary);
  if (!ROM.is_open()) {
    error("failed to open ROM file: %s", data);
    return;
  }

  // gemini carry
  u32 addr = base;
  char byte;

  while (ROM.get(byte) && addr <= 0xFFFF) {
    ctx.bus.write(static_cast<u16>(addr++), static_cast<u8>(byte));
  }
  ok("loaded ROM into memory (%u bytes)", addr - 0x8000);

  Reset();
}

inline void VM::dbgState(u8 opcode) {
  printf("PC:%04X\n OP:%02X\n A:%02X Y: %02X SP: %02X", ctx.regs.PC, opcode,
         ctx.regs.A, ctx.regs.Y, ctx.regs.SP);
  printf("CF:%c ; ZF:%c ; ID:%c ; DM:%c ; BC:%c ; OF:%c ; NF%c",
         ctx.regs.flags.CF, ctx.regs.flags.ZF, ctx.regs.flags.ID,
         ctx.regs.flags.DM, ctx.regs.flags.BC, ctx.regs.flags.OF,
         ctx.regs.flags.NF);
}
