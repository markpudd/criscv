#include <stdlib.h>
#include <stdio.h>
#include "RV32I.h"
#include "alu.h"
#include "alu2.h"
#include "branch.h"
#include "load.h"
#include "sb.h"

uint32_t pc;
uint32_t regs[32];

uint8_t *mem;

int debug=1;

// returns r type
dec_inst decode_instruction(uint32_t inst) {
  dec_inst ret;
  ret.raw = inst;
  ret.opcode = inst & 0x7F;
  ret.rd    = (inst >> 7) & 0x1F;
  ret.funct3 = (inst >> 12) & 0x07;
  ret.rs1    = (inst >> 15) & 0x1F;
  ret.rs2    = (inst >> 20) & 0x1F;

  ret.funct7    = (inst >> 25) & 0x7F ;
  ret.imm =0;
  return ret;
}

void dump_regsiters() {
      printf("PC=%08X\n",pc);
      for(int i=0;i<32;i++) {
        printf("x%2d=%08X\n",i,regs[i]);
      }
}


void dump_instruction(dec_inst dinst) {
  printf("Opcode\tFunt3\trs1\trs2\trd\tFunt7\tIMM\n");

  printf("%02X\t%02X\t%02X\t%02X\t%02X\t%02X\t%08X\n",
          dinst.opcode,
          dinst.funct3,
          dinst.rs1,
          dinst.rs2,
          dinst.rd,
          dinst.funct7,
          dinst.imm);
}

void sbreak() {
  printf("Break\n");
}
void init_memory(uint8_t *m) {
    mem = m;
    regs[0] = 0x0;
    pc = 0x0;
}

void set_pc(uint32_t p) {
  pc = p;
}

void set_sp(uint32_t p) {
  regs[2]= p;
}


int step() {

  uint32_t instruction =  *(uint32_t*)(mem+pc);
  printf("Ins=%08X\n",instruction);

  dec_inst dinst = decode_instruction(instruction);
  dump_instruction(dinst);

  pc += 4;
  switch(dinst.opcode) {
    case 0b0110111:   // LUI
        tou(dinst);
        dump_instruction(dinst);
        lui(dinst);
        break;
    case 0b0010111:   // AUIPC
        tou(dinst);
        dump_instruction(dinst);
        auipc(dinst);
        break;
    case 0b1101111:   // JAL
        toj(dinst);
        extend20(dinst);
        dump_instruction(dinst);
        jal(dinst);
        break;
    case 0b1100111:   // JALR
        toi(dinst);
        dump_instruction(dinst);
        jalr(dinst);
        break;
    case 0b1100011:   // Branches
        tos(dinst);
        extend12(dinst);
        dump_instruction(dinst);
        run_branch(dinst);
        break;
    case 0b0000011:   // Loads
        toi(dinst);
        dump_instruction(dinst);
        run_load(dinst);
        break;
    case 0b0100011:   // SB
        tos(dinst);
        dump_instruction(dinst);
        run_sb(dinst);
        break;
    case 0b0010011:   // A.L.U.
        toi(dinst);
        dump_instruction(dinst);
        run_alu(dinst);
        break;
    case 0b0110011:  // ALU2
        dump_instruction(dinst);
        run_alu2(dinst);
        break;
    case 0b0001111:  // Fence
        dump_instruction(dinst);
        fence(dinst);
        break;
    case 0b1110011:  // ECALL/EBREAK
        dump_instruction(dinst);
        dinst.rs2 == 0 ? ecall(dinst) : ebreak(dinst);
        break;
    default:
        perr(dinst);
        break;
  }

  return 0;
}

int run() {
  while(1) {
    step();
  }
}


void perr(dec_inst inst)  {
  //  printf("Misformed instruction\n" );
    exit(1);
}

void lui(dec_inst inst)  {
    regs[inst.rd] = inst.raw & 0xFFFFF000;
}


void auipc(dec_inst inst)  {
  regs[inst.rd] = pc+inst.raw & 0xFFFFF000;

}

void jal(dec_inst inst)  {
    pc = pc+inst.imm;
}

void jalr(dec_inst inst)  {
    extend12(inst);
    pc = pc+inst.rs1+inst.imm;
}

void fence(dec_inst inst)  {
  sbreak();

}

void ecall(dec_inst inst)  {
    sbreak();
}

void ebreak(dec_inst inst)  {
    sbreak();
}
