#include <stdio.h>
#include <stdlib.h>
#include "RV32I.h"

int main(int argc, char const *argv[]) {
  // Allocate 32K of storage
  uint8_t * memory = malloc(32768);

  // load at 0x0
  FILE *fp;
  fp = fopen(argv[1], "rb");
  if(fp == NULL) {
    fprintf(stderr, "No such file!\n");
    exit(1);
  }
  int n = fread(memory, 1, 32768, fp);
  printf("Loaded %d bytes\n",n);
  // initialize
  init_memory(memory);
  set_pc(0x0);
  set_sp(512);
  //run
  //run();

  while(1) {
    step();
    dump_regsiters();
    getchar();
  }
  printf("Number at 1024=%c\n",memory[1024]);

  return 0;
}
