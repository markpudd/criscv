#include "load.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;

void (*ld_fn[])(dec_inst) = {lb, lh, lw, lbu, lhu, perr, perr, perr};

void run_load(dec_inst inst) {

  return (*ld_fn[inst.funct3]) (inst);
}


void lb(dec_inst inst)  {
  extend12(inst);
  regs[inst.rd] = *(int8_t*)(mem+(int32_t)(regs[inst.rs1]+inst.imm));
}

void lh(dec_inst inst)  {
  extend12(inst);
  regs[inst.rd] = *(int16_t*)(mem+(int32_t)(regs[inst.rs1]+inst.imm));
}

void lw(dec_inst inst)  {
  extend12(inst);
  regs[inst.rd] = *(int32_t*)(mem+(int32_t)(regs[inst.rs1]+inst.imm));
}

void lbu(dec_inst inst)  {
  extend12(inst);
  regs[inst.rd] = *(uint8_t*)(mem+(int32_t)(regs[inst.rs1]+inst.imm));
}

void lhu(dec_inst inst)  {
  extend12(inst);
  regs[inst.rd] = *(uint16_t*)(mem+(int32_t)(regs[inst.rs1]+inst.imm));
}
