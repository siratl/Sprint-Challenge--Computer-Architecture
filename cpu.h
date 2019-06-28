#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu
{
  unsigned int pc;
  // registers (array) -- R0->R7 (8 items)
  unsigned char reg[8];
  // ram (array) -- With 8 bits, our CPU has a total of 256 bytes of memory
  unsigned char ram[256];
};

// ALU operations
enum alu_op
{
  ALU_MUL
  // Add more here
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

#define LDI 0b10000010
#define PRN 0b01000111
// TODO: more instructions here. These can be used in cpu_run().
#define HLT 0b00000001
#define MUL 0b10100010

// Function declarations

extern void cpu_load(struct cpu *cpu, char *file);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
