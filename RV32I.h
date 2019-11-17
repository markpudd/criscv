#ifndef __RV32I_H
#define __RV32I_H
#include <stdlib.h>
#include <stdint.h>

typedef struct dec_inst {
  uint32_t raw;
  uint8_t opcode;
  uint8_t funct3;
  uint8_t rs1;
  uint8_t rs2;
  uint8_t rd;
  uint8_t funct7;
  uint32_t imm;
} dec_inst;


// Macros
#define extend12(inst) ((inst.imm >>11 !=0) ?  inst.imm=inst.imm|0xFFFFF000 : inst.imm)
#define extend13(inst) ((inst.imm >>12 !=0) ?  inst.imm=inst.imm|0xFFFFE000 : inst.imm)
#define extend20(inst) ((inst.imm >>19 !=0) ?  inst.imm=inst.imm|0xFFF00000 : inst.imm)


#define toi(inst) (inst.imm = (inst.funct7 << 5) | inst.rs2)
#define tou(inst) (inst.imm = (inst.funct7 << 25) | (inst.rs2 << 20) | (inst.rs2 << 3) |inst.funct3 )

#define tob(inst) (inst.imm = (inst.funct7 << 5) | inst.rd)

#define tos(inst) (inst.imm = ( ((inst.funct7 &  0x3f) << 5) | (inst.rd & 0x1e) | ((inst.rd &0x1) << 11)  | ((inst.rd &0x40) << 6)))
#define toj(inst) (inst.imm = (inst.raw & 0xff000) | ((inst.raw & 0x0100) >> 9)  | ((inst.raw & 0x7fc00000)>>18) | ((inst.raw & 0x80000000) >>11 ))



#define endianFlip(input)  (input >> 24 & 0xff) | (input >> 8 & 0xff00) |  (input << 8 & 0xff0000) |  (input << 24 & 0xff000000)




void dump_regsiters();

void dump_instruction(dec_inst dinst) ;

void set_pc(uint32_t p);
void set_sp(uint32_t p);

dec_inst decode_instruction(uint32_t inst) ;
void init_memory(uint8_t *m);
int step();
int run();

void perr(dec_inst inst);

void lui(dec_inst inst);


void auipc(dec_inst inst);

void jal(dec_inst inst);

void jalr(dec_inst inst);

void fence(dec_inst inst);

void ecall(dec_inst inst);

void ebreak(dec_inst inst);

#endif
