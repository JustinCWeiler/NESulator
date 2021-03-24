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

	// fake internal state
	uint8_t cycles_left;
} cpu_t;

cpu_t* cpu_create(bus_t* bus);
void cpu_reset(cpu_t* cpu);
void cpu_pulse(cpu_t* cpu);
void cpu_print_state(cpu_t* cpu);

// Flags
uint8_t get_car(cpu_t* cpu);
uint8_t get_zer(cpu_t* cpu);
uint8_t get_ida(cpu_t* cpu);
uint8_t get_dec(cpu_t* cpu);
uint8_t get_brk(cpu_t* cpu);
uint8_t get_ovf(cpu_t* cpu);
uint8_t get_neg(cpu_t* cpu);

void set_car(cpu_t* cpu);
void set_zer(cpu_t* cpu);
void set_ida(cpu_t* cpu);
void set_dec(cpu_t* cpu);
void set_brk(cpu_t* cpu);
void set_ovf(cpu_t* cpu);
void set_neg(cpu_t* cpu);

void clr_car(cpu_t* cpu);
void clr_zer(cpu_t* cpu);
void clr_ida(cpu_t* cpu);
void clr_dec(cpu_t* cpu);
void clr_brk(cpu_t* cpu);
void clr_ovf(cpu_t* cpu);
void clr_neg(cpu_t* cpu);

#endif
