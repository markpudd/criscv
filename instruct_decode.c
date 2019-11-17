#include <stdio.h>
#include <stdlib.h>
#include "RV32I.h"

int main(int argc, char const *argv[]) {

  uint32_t input;
  uint32_t inst=0;
  sscanf(argv[1],"%x", &input);

  // convert endian
//  inst = (input >> 24 & 0xff) | (input >> 8 & 0xff00) |  (input << 8 & 0xff0000) |  (input << 24 & 0xff000000);
  inst = input;

  dec_inst dinst =  decode_instruction(inst);
  uint8_t opcode;
  uint8_t funct3;
  uint8_t rs1;
  uint8_t rs2;
  uint8_t rd;
  uint32_t funct7;
  uint32_t imm;

  tos(dinst);
  extend12(dinst);

  printf("Opcode=%02X\n",dinst.opcode);
  printf("Funt3=%02X\n",dinst.funct3);
  printf("rs1=%02X\n",dinst.rs1);
  printf("rs2=%02X\n",dinst.rs2);
  printf("rd=%02X\n",dinst.rd);
  printf("Funt7=%02X\n",dinst.funct7);
  printf("Imm=%08X\n",dinst.imm);

  return 0;
}
