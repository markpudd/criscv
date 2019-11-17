#ifndef __LOAD_H
#define __LOAD_H
#include "RV32I.h"


void run_load(dec_inst inst);

void lb(dec_inst inst);

void lh(dec_inst inst);

void lw(dec_inst inst);

void lbu(dec_inst inst);

void lhu(dec_inst inst);

#endif
