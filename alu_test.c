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
  // TODO
}

void sltiu_test() {
  // TODO
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
  // TODO
}

void srli_srai_test() {
  // TODO
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
