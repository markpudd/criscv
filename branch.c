#include "branch.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;

void (*branch_fn[])(dec_inst) = {beq,
                                 bne,
                                 perr,
                                 perr,
                                 blt,
                                 bge,
                                 bltu,
                                 bgeu};


void run_branch(dec_inst inst) {
 return (*branch_fn[inst.funct3]) (inst);
}


void beq(dec_inst inst)  {
    if((int32_t)regs[inst.rs1] == (int32_t)regs[inst.rs2]) {
      pc = pc+inst.imm;
    }
}

void bne(dec_inst inst)  {
    if((int32_t)regs[inst.rs1] != (int32_t)regs[inst.rs2]) {
      pc = pc+inst.imm;
    }
}

void blt(dec_inst inst)  {
    if((int32_t)regs[inst.rs1] < (int32_t)regs[inst.rs2]) {
      pc = pc+inst.imm;
    }
}

void bge(dec_inst inst)  {
    if((int32_t)regs[inst.rs1] >= (int32_t)regs[inst.rs2]) {
      pc = pc+inst.imm;
    }
}


void bltu(dec_inst inst)  {
    if(regs[inst.rs1] < regs[inst.rs2]) {
      pc = pc+inst.imm;
    }
}

void bgeu(dec_inst inst)  {
    if(regs[inst.rs1] >= regs[inst.rs2]) {
      pc = pc+inst.imm-1;
    }
}
