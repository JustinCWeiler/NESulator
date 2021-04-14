#ifndef BUS_H
#define BUS_H

#include "flags.h"
#include <stdint.h>

#define PRG_CHUNK 0x4000
#define CHR_CHUNK 0x2000

// terrible disgusting god awful
// please for the love of god change
// this later you piece of filth
#define bus_read(bus, addr) ((bus)->read((bus), (addr)))
#define bus_write(bus, addr, val) ((bus)->write((bus), (addr), (val)))

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

uint16_t addr_wrap(uint16_t addr);

#endif
