#include "alu2.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;

void (*alu2_fn[])(dec_inst) = {add_sub,
                                 sll,
                                 slt,
                                 sltu,
                                 xor,
                                 srl_sra,
                                 or,
                                 and};


void run_alu2(dec_inst inst) {
   (*alu2_fn[inst.funct3]) (inst);
}

void add_sub(dec_inst inst) {
    if((inst.funct7 & 0b1000000) == 0)
      regs[inst.rd] = regs[inst.rs1]+regs[inst.rs2];
    else
      regs[inst.rd] = regs[inst.rs1]-regs[inst.rs2];
}



void sll(dec_inst inst) {
  regs[inst.rd] = regs[inst.rs1] <<(regs[inst.rs2] &0x1f);
}

void slt(dec_inst inst) {
    regs[inst.rd] = (int32_t)regs[inst.rs1] < (int32_t)regs[inst.rs2]  ? 1 : 0;
}

void sltu(dec_inst inst){
    regs[inst.rd] = (uint32_t)regs[inst.rs1] < (uint32_t)regs[inst.rs2]  ? 1 : 0;
}

void xor(dec_inst inst){
  regs[inst.rd] = regs[inst.rs1]^regs[inst.rs2];
}
void srl_sra(dec_inst inst){
    if((inst.funct7 & 0b1000000) == 0)
      regs[inst.rd] =  (uint32_t)regs[inst.rs1] >> (regs[inst.rs2] &0x1f);
    else
      regs[inst.rd] =  (int32_t)regs[inst.rs1] >>(regs[inst.rs2] &0x1f);
}

void or(dec_inst inst){
  regs[inst.rd] = regs[inst.rs1]|regs[inst.rs2];
}
void and(dec_inst inst){
  regs[inst.rd] = regs[inst.rs1]&regs[inst.rs2];
}
