#include "bus.h"
#include "flags.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_DONE 0x01

// each mapper file contains 8 definitions,
// meaning the maximum file number should be 0x20
// in reality i'll probably stop before getting there though
#include "mappers/00.c"

typedef void (*create_func)(bus_t*);
typedef uint8_t (*read_func)(bus_t*, uint16_t);
typedef void (*write_func)(bus_t*, uint16_t, uint8_t);

size_t sizes[] = {
	ms00
};

create_func create_funcs[] = {
	mc00
};

read_func read_funcs[] = {
	mr00
};

write_func write_funcs[] = {
	mw00
};

bus_t* bus_create_simple(read_func read, write_func write) {
	bus_t* bus = malloc(sizeof(bus_t));

	bus->read = read;
	bus->write = write;

	return bus;
}

bus_t* bus_create(flags_t flags, void* prg_rom, void* chr_rom) {
	uint8_t mapper = (flags.map_hi << 4) | flags.map_lo;

	if (mapper >= NUM_DONE) {
		printf("Sorry, this game isn't supported yet\n");
		printf("Debug info: Mapper %u\n", mapper);
		return NULL;
	}

	bus_t* bus = malloc(sizes[mapper]);

	bus->read = read_funcs[mapper];
	bus->write = write_funcs[mapper];

	bus->prg_rom = prg_rom;
	bus->chr_rom = chr_rom;

	bus->flags = flags;

	bus->cpu_mem = malloc(0x10000);

	create_funcs[mapper](bus);

	return bus;
}

uint8_t bus_read(bus_t* bus, uint16_t addr) { return bus->read(bus, addr); }
void bus_write(bus_t* bus, uint16_t addr, uint8_t val) { bus->write(bus, addr, val); }

uint16_t addr_wrap(uint16_t addr) {
	if (addr < 0x2000)
		return (addr % 0x800) + 0;
	if (0x2000 <= addr && addr < 0x4000)
		return (addr % 0x8) + 0x2000;
	return addr;
}
