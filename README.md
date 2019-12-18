# criscv
RISC-V RV32I C Emulator

This is a simple RISC-V emulator.   It runs non compressed 32-bit RISC-V instructions.  

# Building and example

The runmem excutable will allow you ro step though some RISV-V and dump state on each step

<pre><code>
   make runmem
</code></pre>

# Running Tests

You can run tests with:-

<pre><code>
   make test
   ./test
</code></pre>

There are still some tests to be completed!

# Embeding

You can emebed the emulator into other executables by including <code>RV32I.h</code> and linking RV32I,alu,alu2,branch and sb.  Then set up some memory and initailize with:-

<pre><code>
init_memory(memory);
set_pc(0x0);              // Assume PC is at 0x0
set_sp(512);              // Optional set stack pointer
</code></pre>

You can then step through code with

<pre><code>
step();
dump_regsiters();  // Optionally dump registers
</code></pre>

# Running code built with GCC (RISC-V)

It possible to run simple code built with gcc however system calls will not work.  

TODO add simple tutorial for this

fence, ecall and ebreak currently just call sbreak which outputs some text.   This will be changed to a call back in a later revision.
