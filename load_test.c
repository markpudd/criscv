#include "runtest.h"
#include "load.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;


void lb_test() {
  TEST_NOT_IMPLEMENTED("lb");
}

void lh_test() {
  TEST_NOT_IMPLEMENTED("lh");
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
