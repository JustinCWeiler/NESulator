#ifndef BUS_H
#define BUS_H

#include "flags.h"
#include <stdint.h>

#define PRG_CHUNK 0x4000
#define CHR_CHUNK 0x2000

typedef struct bus {
	uint8_t (*read)(struct bus*, uint16_t);
	void (*write)(struct bus*, uint16_t, uint8_t);

	void* prg_rom;
	void* chr_rom;

	flags_t flags;

	char* cpu_mem;
} bus_t;

bus_t* bus_create_simple(uint8_t (*read)(bus_t*, uint16_t),
                         void (*write)(bus_t*, uint16_t, uint8_t));

bus_t* bus_create(flags_t flags, void* prg_rom, void* chr_rom);

uint8_t bus_read(bus_t* bus, uint16_t addr);
void bus_write(bus_t* bus, uint16_t addr, uint8_t val);

uint16_t addr_wrap(uint16_t addr);

#endif
