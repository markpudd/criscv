#ifndef __ALU_H
#define __ALU_H
#include "RV32I.h"

void run_alu(dec_inst inst);
void addi(dec_inst inst);
void slti(dec_inst inst);
void sltiu(dec_inst inst);
void xori(dec_inst inst);
void ori(dec_inst inst);
void andi(dec_inst inst);

void slli(dec_inst inst);
void srli_srai(dec_inst inst);

#endif
