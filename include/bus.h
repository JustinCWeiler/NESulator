#ifndef BUS_H
#define BUS_H

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
	uint8_t prg_size;
	void* chr_rom;
	uint8_t chr_size;
} bus_t;

bus_t* bus_create_simple(uint8_t (*read)(bus_t*, uint16_t),
                         void (*write)(bus_t*, uint16_t, uint8_t));

bus_t* bus_create(uint8_t num, void* prg_rom, uint8_t prg_size,
                                     void* chr_rom, uint8_t chr_size);

#endif
