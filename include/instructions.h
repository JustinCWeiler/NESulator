#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"
#include <stdint.h>

typedef uint16_t (*addr_func)(cpu_t*);
typedef void (*inst_func)(cpu_t*, uint8_t, uint16_t);

uint16_t get_addr(cpu_t* cpu, uint8_t op);
void execute_instruction(cpu_t* cpu, uint8_t op, uint16_t addr);
uint8_t get_base_cycles(uint8_t op);

#endif
