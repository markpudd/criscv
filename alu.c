#include "alu.h"


extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;


void (*alu_fn[])(dec_inst) = {addi,
                                 slli,
                                 slti,
                                 sltiu,
                                 xori,
                                 srli_srai,
                                 ori,
                                 andi};


void run_alu(dec_inst inst) {
  (*alu_fn[inst.funct3]) (inst);
}

void addi(dec_inst inst) {
  extend12(inst);
  regs[inst.rd] = (int32_t)regs[inst.rs1]+inst.imm;
}

void slti(dec_inst inst){
    extend12(inst);
    regs[inst.rd] = (int32_t)regs[inst.rs1] < (int32_t)inst.imm ? 1 : 0;
}

void sltiu(dec_inst inst){
  extend12(inst);
  regs[inst.rd] = (uint32_t)regs[inst.rs1] < (uint32_t)inst.imm ? 1 : 0;
}

void xori(dec_inst inst){
  extend12(inst);
  regs[inst.rd] = (int32_t)regs[inst.rs1] ^ inst.imm;
}

void ori(dec_inst inst){
  extend12(inst);
  regs[inst.rd] = (int32_t)regs[inst.rs1] | inst.imm;
}

void andi(dec_inst inst){
  extend12(inst);
  regs[inst.rd] = (int32_t)regs[inst.rs1] & inst.imm;
}


void slli(dec_inst inst){
  regs[inst.rd] = regs[inst.rs1] << inst.imm;

}

void srli_srai(dec_inst inst){
  if((inst.funct7 & 0b1000000) == 0)
    regs[inst.rd] =  (uint32_t)regs[inst.rs1] >> (inst.imm &0x1F);
  else
    regs[inst.rd] =  (int32_t)regs[inst.rs1] >> (inst.imm &0x1F);
}
