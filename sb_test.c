#include "runtest.h"
#include "sb.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;

void sb_test() {
  TEST_NOT_IMPLEMENTED("sb");
}

void sh_test() {
  TEST_NOT_IMPLEMENTED("sh");
}

void sw_test() {
  TEST_NOT_IMPLEMENTED("sw");
}

void run_sb_tests() {
  sb_test();
  sh_test();
  sw_test();
}
