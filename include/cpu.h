#ifndef CPU_H
#define CPU_H

#include "bus.h"
#include <stdint.h>

typedef struct {
	uint8_t A;	// accumulator
	uint8_t X, Y;	// index registers
	uint16_t PC;	// program counter
	uint8_t S;	// stack pointer
	uint8_t P;	// status register
} register_t;

typedef struct {
	// real internal state
	register_t reg;

	// real external connection
	bus_t* bus;
} cpu_t;

cpu_t* cpu_create(bus_t* bus);

void cpu_reset(cpu_t* cpu);

void cpu_clock(cpu_t* cpu);

void cpu_print_state(cpu_t* cpu);

// Flags
uint8_t cpu_get_car(cpu_t* cpu);
uint8_t cpu_get_zer(cpu_t* cpu);
uint8_t cpu_get_ida(cpu_t* cpu);
uint8_t cpu_get_dec(cpu_t* cpu);
uint8_t cpu_get_ovf(cpu_t* cpu);
uint8_t cpu_get_neg(cpu_t* cpu);

void cpu_set_car(cpu_t* cpu);
void cpu_set_zer(cpu_t* cpu);
void cpu_set_ida(cpu_t* cpu);
void cpu_set_dec(cpu_t* cpu);
void cpu_set_ovf(cpu_t* cpu);
void cpu_set_neg(cpu_t* cpu);

void cpu_clr_car(cpu_t* cpu);
void cpu_clr_zer(cpu_t* cpu);
void cpu_clr_ida(cpu_t* cpu);
void cpu_clr_dec(cpu_t* cpu);
void cpu_clr_ovf(cpu_t* cpu);
void cpu_clr_neg(cpu_t* cpu);

#endif
