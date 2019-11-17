#include "runtest.h"
#include "alu2.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;

dec_inst alu2_setup_test() {
  dec_inst inst;
  inst.opcode = 0b0110011;
  inst.rs1=1;
  inst.rs2=2;
  inst.rd=3;
  inst.funct7=0b0000000;
  inst.imm=0;
  return inst;
}

void add_sub_test() {
  dec_inst inst = alu2_setup_test();
  inst.funct3=0b000;
  regs[1] = 1;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("add_sub add less test", regs[3],3);
  regs[1] = 0xFFFFFFFD;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("add_sub add neg num test", regs[3],-1);
  inst.funct7=0b1000000;
  regs[1] = 5;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("add_sub sub less test", regs[3],3);
  regs[1] = 0xFFFFFFFD;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("add_sub sub neg num test", regs[3],-5);
}

void sll_test() {
  dec_inst inst = alu2_setup_test();
  inst.funct3=0b001;
  regs[1] = 0b11;
  regs[2] = 0b10;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("sll shift test", regs[3],0b1100);
  regs[1] = 0b11;
  regs[2] = 0b100010;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("sll shift test more 5 bits", regs[3],0b1100);
}

void slt_test() {
  dec_inst inst = alu2_setup_test();
  inst.funct3=0b010;
  regs[1] = 1;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("slt less test", regs[3],1);
  regs[1] = 2;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("slt equal test", regs[3],0);
  regs[1] = 3;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("slt more test", regs[3],0);
  regs[1] =  0xFFFFFFFD; // -3;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("slt neg num test", regs[3],1);
}

void sltu_test() {
  dec_inst inst = alu2_setup_test();
  inst.funct3=0b011;
  regs[1] = 1;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("sltu less test", regs[3],1);
  regs[1] = 2;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("sltu equal test", regs[3],0);
  regs[1] = 3;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("sltu more test", regs[3],0);
  regs[1] = 0xFFFFFFFD;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("sltu neg num test", regs[3],0);
}

void xor_test() {
  dec_inst inst = alu2_setup_test();
  inst.funct3=0b100;
  regs[1] = 0x34f2a64c;
  regs[2] = 0x9f5aac32;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("xor test", regs[3],(0x34f2a64c ^ 0x9f5aac32));

}

void srl_sra_test() {
  dec_inst inst = alu2_setup_test();
  inst.funct3=0b101;
  regs[1] = 8;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("srl_sra srl test", regs[3],2);
  regs[1] = 8;
  regs[2] = 0b100010;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("srl_sra srl test (more 5 bits)", regs[3],2);
  regs[1] = 0xffffffff;
  regs[2] = 0b10;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("srl_sra srl test neg", regs[3],0x3fffffff);
  inst.funct7=0b1000000;
  regs[1] = 8;
  regs[2] = 2;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("srl_sra sra test", regs[3],2);
  regs[1] = 8;
  regs[2] = 0b100010;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("srl_sra sra test (more 5 bits)", regs[3],2);
  regs[1] = 0xffffffff;
  regs[2] = 0b10;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("srl_sra sra test neg", regs[3],0xffffffff);

}

void or_test() {
  dec_inst inst = alu2_setup_test();
  inst.funct3=0b110;
  regs[1] = 0x34f2a64c;
  regs[2] = 0x9f5aac32;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("or test", regs[3],(0x34f2a64c | 0x9f5aac32));

}

void and_test() {
  dec_inst inst = alu2_setup_test();
  inst.funct3=0b111;
  regs[1] = 0x34f2a64c;
  regs[2] = 0x9f5aac32;
  run_alu2(inst);
  TEST_EQUALS_ASSERT("and test", regs[3],(0x34f2a64c & 0x9f5aac32));
}

void run_alu2_tests() {
  and_test();
  xor_test();
  or_test();
  add_sub_test();
  sll_test();
  slt_test();
  sltu_test();
  srl_sra_test();
}
