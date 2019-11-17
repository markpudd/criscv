#include <stdio.h>
#include "alu2_test.h"
#include "alu_test.h"
#include "RV32I.h"

int _tests_run;
int _tests_fail;
void TEST_EQUALS_ASSERT(char * test_name, uint32_t a1,uint32_t a2) {
  _tests_run++;
  if(a1 == a2) {
    printf("\033[0;32mPASS\033[0m - %s\n",test_name);
  } else {
    printf("\033[0;31mFAIL\033[0m - %s\n",test_name);
    _tests_fail++;
  }
}

int main(int argc, char const *argv[]) {
   _tests_run=0;
   _tests_fail=0;
  uint8_t * memory = malloc(1024);
  init_memory(memory);
  set_pc(0x0);
  set_sp(512);
  run_alu2_tests();
  run_alu_tests();
  printf("%d/%d tests passed\n",_tests_run-_tests_fail,_tests_run);
  if(_tests_fail) {
    printf("\033[0;31m%d FAILED TESTS\033[0m\n",_tests_fail);
  }
  return _tests_fail;
}
