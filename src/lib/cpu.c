#include "cpu.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

cpu_t* cpu_create(bus_t* bus) {
	cpu_t* cpu = malloc(sizeof(cpu_t));

	cpu->bus = bus;

	cpu_reset(cpu);

	return cpu;
}

void cpu_reset(cpu_t* cpu) {
	cpu->reg.A = 0;
	cpu->reg.X = 0;
	cpu->reg.Y = 0;
	cpu->reg.P = 0x34;
	cpu->reg.S = 0xfd;

	uint8_t lo = cpu->bus->read(0xFFFC);
	uint8_t hi = cpu->bus->read(0xFFFD);

	cpu->reg.PC = (hi << 8) | lo;
}

void cpu_clock(cpu_t* cpu) {
	// TODO
	(void)cpu;
}

uint8_t cpu_get_car(cpu_t* cpu) { return (cpu->reg.P >> 0) & 1; }
uint8_t cpu_get_zer(cpu_t* cpu) { return (cpu->reg.P >> 1) & 1; }
uint8_t cpu_get_ida(cpu_t* cpu) { return (cpu->reg.P >> 2) & 1; }
uint8_t cpu_get_dec(cpu_t* cpu) { return (cpu->reg.P >> 3) & 1; }
uint8_t cpu_get_ovf(cpu_t* cpu) { return (cpu->reg.P >> 6) & 1; }
uint8_t cpu_get_neg(cpu_t* cpu) { return (cpu->reg.P >> 7) & 1; }

void cpu_set_car(cpu_t* cpu) { cpu->reg.P |= (1 << 0); }
void cpu_set_zer(cpu_t* cpu) { cpu->reg.P |= (1 << 1); }
void cpu_set_ida(cpu_t* cpu) { cpu->reg.P |= (1 << 2); }
void cpu_set_dec(cpu_t* cpu) { cpu->reg.P |= (1 << 3); }
void cpu_set_ovf(cpu_t* cpu) { cpu->reg.P |= (1 << 6); }
void cpu_set_neg(cpu_t* cpu) { cpu->reg.P |= (1 << 7); }

void cpu_clr_car(cpu_t* cpu) { cpu->reg.P &= ~(1 << 0); }
void cpu_clr_zer(cpu_t* cpu) { cpu->reg.P &= ~(1 << 1); }
void cpu_clr_ida(cpu_t* cpu) { cpu->reg.P &= ~(1 << 2); }
void cpu_clr_dec(cpu_t* cpu) { cpu->reg.P &= ~(1 << 3); }
void cpu_clr_ovf(cpu_t* cpu) { cpu->reg.P &= ~(1 << 6); }
void cpu_clr_neg(cpu_t* cpu) { cpu->reg.P &= ~(1 << 7); }

void cpu_print_state(cpu_t* cpu) {
	printf("---------- CPU State ----------\n");
	printf("           registers           \n");
	printf("A:   0x%02x\n", cpu->reg.A);
	printf("X:   0x%02x\n", cpu->reg.X);
	printf("Y:   0x%02x\n", cpu->reg.Y);
	printf("S:   0x%02x\n", cpu->reg.S);
	printf("PC:  0x%04x\n", cpu->reg.PC);
	printf("             flags             \n");
	printf("car: %d\n", cpu_get_car(cpu));
	printf("zer: %d\n", cpu_get_zer(cpu));
	printf("ida: %d\n", cpu_get_ida(cpu));
	printf("dec: %d\n", cpu_get_dec(cpu));
	printf("ovf: %d\n", cpu_get_ovf(cpu));
	printf("neg: %d\n", cpu_get_neg(cpu));
	printf("-------------------------------\n");
}
