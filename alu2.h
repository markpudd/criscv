#ifndef __ALU2_H
#define __ALU2_H
#include "RV32I.h"

void run_alu2(dec_inst inst);
void add_sub(dec_inst inst);
void sll(dec_inst inst);
void slt(dec_inst inst);
void sltu(dec_inst inst);
void xor(dec_inst inst);
void srl_sra(dec_inst inst);
void or(dec_inst inst);
void and(dec_inst inst);


#endif
