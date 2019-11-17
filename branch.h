#ifndef __BRANCH_H
#define __BRANCH_H
#include "RV32I.h"

void run_branch(dec_inst inst);
void beq(dec_inst inst);

void bne(dec_inst inst);

void blt(dec_inst inst);

void bge(dec_inst inst);

void bltu(dec_inst inst);

void bgeu(dec_inst inst);

#endif
