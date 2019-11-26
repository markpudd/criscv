#include "runtest.h"
#include "branch.h"

extern uint32_t pc;
extern uint32_t regs[32];
extern uint8_t *mem;

void beq_test() {
  TEST_NOT_IMPLEMENTED("beq");
}
void bne_test() {
  TEST_NOT_IMPLEMENTED("bne");
}

void blt_test() {
  TEST_NOT_IMPLEMENTED("blt");
}

void bge_test() {
  TEST_NOT_IMPLEMENTED("bge");
}

void bltu_test() {
  TEST_NOT_IMPLEMENTED("bltu");
}

void bgeu_test() {
  TEST_NOT_IMPLEMENTED("bgeu");
}

void run_branch_tests() {
  beq_test();
  bne_test();
  blt_test();
  bge_test();
  bltu_test();
  bgeu_test();

}
