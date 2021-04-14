#include "bus.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_DONE 0x00

typedef void (*create_func)(bus_t*);
typedef uint8_t (*read_func)(bus_t*, uint16_t);
typedef void (*write_func)(bus_t*, uint16_t, uint8_t);

// array of pointer to create_funcs
// would make typedef but its complicated
create_func create_funcs[] = {
};

read_func read_funcs[] = {
};

write_func write_funcs[] = {
};

bus_t* bus_create_simple(read_func read, write_func write) {
	bus_t* bus = malloc(sizeof(bus_t));

	bus->read = read;
	bus->write = write;

	return bus;
}

bus_t* bus_create(uint8_t num, void* prg_rom, uint8_t prg_size,
                                     void* chr_rom, uint8_t chr_size) {
	if (num >= NUM_DONE) {
		printf("Sorry, this game isn't supported yet\n");
		return NULL;
	}

	bus_t* bus = malloc(sizeof(bus_t));

	bus->read = read_funcs[num];
	bus->write = write_funcs[num];

	bus->prg_rom = prg_rom;
	bus->prg_size = prg_size;
	bus->chr_rom = chr_rom;
	bus->chr_size = chr_size;

	return bus;
}
