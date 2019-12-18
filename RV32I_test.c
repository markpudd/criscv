#include "runtest.h"
#include "RV32I.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;

uint32_t jtest_table[] =
      { 0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
        0x0,0x0,
      };

void lui_test() {
  dec_inst inst;
  // probably should test raw
  uint32_t instruction =0x800010B7;
  mem = &instruction;
  pc =0;
  regs[1]=0xaabbccdd;
  step();
  TEST_EQUALS_ASSERT("lui test", regs[1],0x80001000);
}

void auipc_test() {
  uint32_t mema[] = {0x0,0x0,0x80001097};
  uint32_t instruction =0x80001097;
  mem = mema;
  pc =8;
  regs[1]=0xaabbccdd;
  step();
  TEST_EQUALS_ASSERT("auipc test", regs[1],0x80001008);

}

void jal_test() {
  TEST_NOT_IMPLEMENTED("jal");
}

void jalr_test() {
  TEST_NOT_IMPLEMENTED("jalr");
}

void fence_test() {
  TEST_NOT_IMPLEMENTED("fence");
}

void ecall_test() {
  TEST_NOT_IMPLEMENTED("ecall");
}

void ebreak_test() {
  TEST_NOT_IMPLEMENTED("ebreak");
}

void toj_test() {





}

void run_rv32i_tests() {
  lui_test();
  auipc_test();
  jal_test();
  jalr_test();
  fence_test();
  ecall_test();
  ebreak_test();
}
