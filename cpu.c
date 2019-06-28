#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Read RAM inside CPU struct at given index
 */
unsigned char cpu_ram_read(struct cpu *cpu, unsigned int index)
{
    return cpu->ram[index];
}

/**
 * Write a value to the RAM inside CPU struct at given index
 */
void cpu_ram_write(struct cpu *cpu, unsigned int index, unsigned char value)
{
    cpu->ram[index] = value;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *file)
{

    FILE *fp;
    char line[128];

    int address = 0;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error - Opening File Failed\n");
        exit(1);
    }
    while (fgets(line, 128, fp) != NULL)
    {
        char *endptr;
        unsigned char value = strtoul(line, &endptr, 2);

        if (line == endptr)
        {
            continue;
        }

        cpu->ram[address++] = value;
    }
    fclose(fp);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
    switch (op)
    {
    case ALU_MUL:
        // TODO
        cpu->ram[regA] = cpu->ram[regA] * cpu->ram[regB];
        break;
    }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
    int running = 1; // True until we get a HLT instruction

    while (running)
    {
        // TODO
        // 1. Get the value of the current instruction (in address PC).
        unsigned char IR = cpu_ram_read(cpu, cpu->pc);
        // 2. Figure out how many operands this next instruction requires
        int operands = IR >> 6;
        // 3. Get the appropriate value(s) of the operands following this instruction
        unsigned char operandA, operandB;
        if (operands > 0)
        {
            operandA = cpu_ram_read(cpu, cpu->pc + 1);
            if (operands > 1)
            {
                operandB = cpu_ram_read(cpu, cpu->pc + 2);
            }
        }
        // 4. switch() over it to decide on a course of action.
        switch (IR)
        // 5. Do whatever the instruction should do according to the spec.
        {
        case LDI:
            cpu_ram_write(cpu, operandA, operandB);
            break;
        case PRN:
            printf("%d\n", cpu_ram_read(cpu, operandA));
            break;
        case MUL:
            alu(cpu, ALU_MUL, operandA, operandB);
            break;
        case HLT:
            running = 0;
            break;
        default:
            printf("Error - Instruction Register Unknown at register PC index {%d}\n", cpu->pc);
            running = 0;
            break;
        }
        // 6. Move the PC to the next instruction.
        cpu->pc += operands + 1;
    }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
    // TODO: Initialize the PC and other special registers

    // * `R0`-`R6` are cleared to `0`.
    memset(cpu->reg, 0, 8 * sizeof(unsigned char));

    // * `R7` is set to `0xF4`.
    cpu->reg[7] = 0xF4;

    // * `PC` and `FL` registers are cleared to `0`.
    cpu->pc = 0;

    // * RAM is cleared to `0`.
    memset(cpu->ram, 0, 256 * sizeof(unsigned char));
}