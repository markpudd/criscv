#include "sb.h"
extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;
void (*sb_fn[])(dec_inst) = {sb, sh, sw, perr, perr, perr, perr, perr};

void run_sb(dec_inst inst) {
 return (*sb_fn[inst.funct3]) (inst);
}


void sb(dec_inst inst) {
  extend12(inst);
  *(uint8_t*)(mem+(int32_t)(regs[inst.rs1]+inst.imm)) = (uint8_t)regs[inst.rs2];
}
void sh(dec_inst inst) {
  extend12(inst);
  *(uint16_t*)(mem+(int32_t)(regs[inst.rs1]+inst.imm)) = (uint16_t)regs[inst.rs2];
}
void sw(dec_inst inst) {
  extend12(inst);
  *(uint32_t*)(mem+(int32_t)(regs[inst.rs1]+inst.imm)) = regs[inst.rs2];
}
