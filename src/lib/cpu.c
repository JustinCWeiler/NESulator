#include "cpu.h"
#include "instructions.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

cpu_t* cpu_create(bus_t* bus) {
	cpu_t* cpu = malloc(sizeof(cpu_t));

	cpu->bus = bus;
	cpu->cycles_left = 0;

	cpu_reset(cpu);

	return cpu;
}

void cpu_reset(cpu_t* cpu) {
	cpu->reg.A = 0;
	cpu->reg.X = 0;
	cpu->reg.Y = 0;
	cpu->reg.P = 0x34;
	cpu->reg.S = 0xfd;

	uint8_t lo = cpu->bus->read(RESET_VECTOR_LO);
	uint8_t hi = cpu->bus->read(RESET_VECTOR_HI);

	cpu->reg.PC = (hi << 8) | lo;
}

void cpu_pulse(cpu_t* cpu) {
	if (cpu->cycles_left == 0) {
		uint8_t opcode = cpu->bus->read(cpu->reg.PC++);

		uint16_t addr = get_addr(cpu, opcode);
		execute_instruction(cpu, opcode, addr);

		cpu->cycles_left += get_base_cycles(opcode);
	}
	cpu->cycles_left--;
}

uint8_t get_car(cpu_t* cpu) { return (cpu->reg.P >> 0) & 1; }
uint8_t get_zer(cpu_t* cpu) { return (cpu->reg.P >> 1) & 1; }
uint8_t get_ida(cpu_t* cpu) { return (cpu->reg.P >> 2) & 1; }
uint8_t get_dec(cpu_t* cpu) { return (cpu->reg.P >> 3) & 1; }
uint8_t get_brk(cpu_t* cpu) { return (cpu->reg.P >> 4) & 1; }
uint8_t get_ovf(cpu_t* cpu) { return (cpu->reg.P >> 6) & 1; }
uint8_t get_neg(cpu_t* cpu) { return (cpu->reg.P >> 7) & 1; }

void set_car(cpu_t* cpu) { cpu->reg.P |= (1 << 0); }
void set_zer(cpu_t* cpu) { cpu->reg.P |= (1 << 1); }
void set_ida(cpu_t* cpu) { cpu->reg.P |= (1 << 2); }
void set_dec(cpu_t* cpu) { cpu->reg.P |= (1 << 3); }
void set_brk(cpu_t* cpu) { cpu->reg.P |= (1 << 4); }
void set_ovf(cpu_t* cpu) { cpu->reg.P |= (1 << 6); }
void set_neg(cpu_t* cpu) { cpu->reg.P |= (1 << 7); }

void clr_car(cpu_t* cpu) { cpu->reg.P &= ~(1 << 0); }
void clr_zer(cpu_t* cpu) { cpu->reg.P &= ~(1 << 1); }
void clr_ida(cpu_t* cpu) { cpu->reg.P &= ~(1 << 2); }
void clr_dec(cpu_t* cpu) { cpu->reg.P &= ~(1 << 3); }
void clr_brk(cpu_t* cpu) { cpu->reg.P &= ~(1 << 4); }
void clr_ovf(cpu_t* cpu) { cpu->reg.P &= ~(1 << 6); }
void clr_neg(cpu_t* cpu) { cpu->reg.P &= ~(1 << 7); }

void cpu_print_state(cpu_t* cpu) {
	printf("---------- CPU State ----------\n");
	printf("           registers           \n");
	printf("A:   0x%02x\n", cpu->reg.A);
	printf("X:   0x%02x\n", cpu->reg.X);
	printf("Y:   0x%02x\n", cpu->reg.Y);
	printf("S:   0x%02x\n", cpu->reg.S);
	printf("PC:  0x%04x\n", cpu->reg.PC);
	printf("             flags             \n");
	printf("car: %d\n", get_car(cpu));
	printf("zer: %d\n", get_zer(cpu));
	printf("ida: %d\n", get_ida(cpu));
	printf("dec: %d\n", get_dec(cpu));
	printf("brk: %d\n", get_brk(cpu));
	printf("ovf: %d\n", get_ovf(cpu));
	printf("neg: %d\n", get_neg(cpu));
	printf("-------------------------------\n");
}
