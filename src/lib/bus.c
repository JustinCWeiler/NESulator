#include "bus.h"
#include <stdlib.h>

bus_t* bus_create(read_func read, write_func write, void* mmap) {
	bus_t* bus = malloc(sizeof(bus_t));

	bus->read = read;
	bus->write = write;
	bus->mmap = mmap;

	return bus;
}

uint8_t bus_read(bus_t* bus, uint16_t addr) {
	return bus->read(addr, bus->mmap);
}

void bus_write(bus_t* bus, uint16_t addr, uint8_t val) {
	bus->write(addr, val, bus->mmap);
}
