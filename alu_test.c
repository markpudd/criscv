#include "runtest.h"
#include "alu.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;

dec_inst alu_setup_test() {
  dec_inst inst;
  inst.opcode = 0b0100011;
  inst.rs1=1;
  inst.rd=3;
  inst.funct7=0b0000000;
  inst.imm=0;
  return inst;
}

void addi_test() {
  dec_inst inst = alu_setup_test();
  inst.funct3=0b000;
  inst.imm =12;
  regs[1] = 31;
  run_alu(inst);
  TEST_EQUALS_ASSERT("addi positive test", regs[3],43);
  inst.imm =0xFFF;
  regs[1] = 31;
  run_alu(inst);
  TEST_EQUALS_ASSERT("addi negative test", regs[3],30);
}
void slti_test() {
  dec_inst inst = alu_setup_test();
  inst.funct3=0b010;
  regs[1] = 1;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("slti less test", regs[3],1);
  regs[1] = 2;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("slti equal test", regs[3],0);
  regs[1] = 3;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("slti more test", regs[3],0);
  regs[1] =  0xFFFFFFFD; // -3;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("slti neg num test", regs[3],1);
}

void sltiu_test() {
  dec_inst inst = alu_setup_test();
  inst.funct3=0b011;
  regs[1] = 1;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("sltui less test", regs[3],1);
  regs[1] = 2;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("sltui equal test", regs[3],0);
  regs[1] = 3;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("sltui more test", regs[3],0);
  regs[1] = 0xFFFFFFFD;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("sltui neg num test", regs[3],0);
}
void xori_test() {
  dec_inst inst = alu_setup_test();
  inst.funct3=0b100;
  inst.imm = 0x1ff;
  regs[1] = 0x9f5aac32;
  run_alu(inst);
  TEST_EQUALS_ASSERT("xori test", regs[3],(0x1ff ^ 0x9f5aac32));
  inst.imm = 0xfff;
  regs[1] = 0x9f5aac32;
  run_alu(inst);
  TEST_EQUALS_ASSERT("xori signed extended test", regs[3],(0xffffffff ^ 0x9f5aac32));
}

void ori_test() {
  dec_inst inst = alu_setup_test();
  inst.funct3=0b110;
  inst.imm = 0x1ff;
  regs[1] = 0x9f5aac32;
  run_alu(inst);
  TEST_EQUALS_ASSERT("ori test", regs[3],(0x1ff | 0x9f5aac32));
  inst.imm = 0xfff;
  regs[1] = 0x9f5aac32;
  run_alu(inst);
  TEST_EQUALS_ASSERT("ori signed extended test", regs[3],(0xffffffff | 0x9f5aac32));

}
void andi_test() {
  dec_inst inst = alu_setup_test();
  inst.funct3=0b111;
  inst.imm = 0x1ff;
  regs[1] = 0x9f5aac32;
  run_alu(inst);
  TEST_EQUALS_ASSERT("andi test", regs[3],(0x1ff & 0x9f5aac32));
  inst.imm = 0xfff;
  regs[1] = 0x9f5aac32;
  run_alu(inst);
  TEST_EQUALS_ASSERT("andi signed extended test", regs[3],(0xffffffff & 0x9f5aac32));

}

void slli_test() {
  dec_inst inst = alu_setup_test();
  inst.funct3=0b001;
  regs[1] = 0b11;
  inst.imm = 0b10;
  run_alu(inst);
  TEST_EQUALS_ASSERT("slli shift test", regs[3],0b1100);
  regs[1] = 0b11;
  inst.imm = 0b100010;
  run_alu(inst);
  TEST_EQUALS_ASSERT("slli shift test more 5 bits", regs[3],0b1100);
}

void srli_srai_test() {
  dec_inst inst = alu_setup_test();
  inst.funct3=0b101;
  regs[1] = 8;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("srli_srai srli test", regs[3],2);
  regs[1] = 8;
  inst.imm = 0b100010;
  run_alu(inst);
  TEST_EQUALS_ASSERT("srli_srai srli test (more 5 bits)", regs[3],2);
  regs[1] = 0xffffffff;
  inst.imm = 0b10;
  run_alu(inst);
  TEST_EQUALS_ASSERT("srli_srai srli test neg", regs[3],0x3fffffff);
  inst.funct7=0b1000000;
  regs[1] = 8;
  inst.imm = 2;
  run_alu(inst);
  TEST_EQUALS_ASSERT("srli_srai srai test", regs[3],2);
  regs[1] = 8;
  inst.imm = 0b100010;
  run_alu(inst);
  TEST_EQUALS_ASSERT("srli_srai srai test (more 5 bits)", regs[3],2);
  regs[1] = 0xffffffff;
  inst.imm = 0b10;
  run_alu(inst);
  TEST_EQUALS_ASSERT("srli_srai srai test neg", regs[3],0xffffffff);
}

void run_alu_tests() {
  addi_test();
  slti_test();
  sltiu_test();
  xori_test();
  ori_test();
  andi_test();
  slli_test();
  srli_srai_test();
}
