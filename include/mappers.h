#ifndef MAPPERS_H
#define MAPPERS_H

#include "bus.h"
#include <stdint.h>

#define NUM_DEFINED 0x01

typedef struct {
	uint8_t* cpu_mem;
	uint8_t prg_rom_size;
	uint8_t prg_ram_size;
} m00_t;

read_func read_funcs[256];
write_func write_funcs[256];

#endif
