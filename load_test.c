#include "runtest.h"
#include "load.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;

uint8_t  test_memory[256];

dec_inst lb_setup_test() {
  dec_inst inst;
  inst.opcode = 0b0000011;
  inst.rs1=1;
  inst.rs2=2;
  inst.rd=3;
  inst.imm=0;
  test_memory[128]=0;
  test_memory[129]=0;
  test_memory[130]=0;
  test_memory[131]=0;
  mem = test_memory;
  return inst;
}

void lb_test() {
  dec_inst inst = lb_setup_test();
  test_memory[131]=0x23;
  inst.funct3=0b000;
  regs[1] = 131;
  regs[2] = 2;
  run_load(inst);
  TEST_EQUALS_ASSERT("lb test", regs[3],0x00000023);
  test_memory[131]=0x23;
  test_memory[128]=0x22;
  inst.funct3=0b000;
  regs[1] = 131;
  regs[2] = 2;
  run_load(inst);
  TEST_EQUALS_ASSERT("lb test (hm)", regs[3],0x00000023);
  test_memory[131]=-5;
  inst.funct3=0b000;
  regs[1] = 131;
  regs[2] = 2;
  run_load(inst);
  TEST_EQUALS_ASSERT("lb neg test", regs[3],-5);
  test_memory[131]=0x23;
  inst.funct3=0b000;
  inst.imm = 10;
  regs[1] = 121;
  regs[2] = 2;
  run_load(inst);
  TEST_EQUALS_ASSERT("lb imm offset positive test", regs[3],0x00000023);
  test_memory[131]=0x23;
  inst.funct3=0b000;
  inst.imm = -10;
  regs[1] = 141;
  regs[2] = 2;
  run_load(inst);
  TEST_EQUALS_ASSERT("lb imm offset neg test", regs[3],0x00000023);
}

void lh_test() {
    dec_inst inst = lb_setup_test();
    test_memory[130]=0x14;
    test_memory[131]=0x23;
    inst.funct3=0b001;
    regs[1] = 130;
    regs[2] = 2;
    run_load(inst);
    TEST_EQUALS_ASSERT("lh test", regs[3],0x00002314);
    test_memory[128]=0x22;
    test_memory[130]=0x14;
    test_memory[131]=0x23;
    inst.funct3=0b001;
    regs[1] = 130;
    regs[2] = 2;
    run_load(inst);
    TEST_EQUALS_ASSERT("lh test (hm)", regs[3],0x00002314);
    test_memory[131]=0xff;
    test_memory[130]=-5;
    inst.funct3=0b001;
    regs[1] = 130;
    regs[2] = 2;
    run_load(inst);
    TEST_EQUALS_ASSERT("lh neg test", regs[3],-5);
    test_memory[130]=0x14;
    test_memory[131]=0x23;
    inst.funct3=0b001;
    inst.imm = 10;
    regs[1] = 120;
    regs[2] = 2;
    run_load(inst);
    TEST_EQUALS_ASSERT("lh imm offset positive test", regs[3],0x00002314);
    test_memory[130]=0x14;
    test_memory[131]=0x23;
    inst.funct3=0b001;
    inst.imm = -10;
    regs[1] = 140;
    regs[2] = 2;
    run_load(inst);
    TEST_EQUALS_ASSERT("lh imm offset neg test", regs[3],0x00002314);
}

void lw_test() {
  TEST_NOT_IMPLEMENTED("lw");
}

void lbu_test() {
  TEST_NOT_IMPLEMENTED("lbu");
}

void lhu_test() {
  TEST_NOT_IMPLEMENTED("lhu");
}


void run_load_tests() {
  lb_test();
  lh_test();
  lw_test();
  lbu_test();
  lhu_test();
}
