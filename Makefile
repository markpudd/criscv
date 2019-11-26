CC=gcc
OBJS = RV32I.o alu.o alu2.o branch.o load.o sb.o
TEST_OBJS = alu2_test.o alu_test.o branch_test.o load_test.o sb_test.o RV32I_test.o

CFLAGS=

test: runtest.o  $(OBJS) $(TEST_OBJS)
		$(CC) -o $@ $^ $(CFLAGS)
runmem: runmem.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
idc: instruct_decode.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm riscv $(OBJ)
