#include "bus.h"
#include <stdlib.h>

bus_t* bus_create(read_func read, write_func write) {
	bus_t* bus = malloc(sizeof(bus_t));

	bus->read = read;
	bus->write = write;

	return bus;
}

uint8_t bus_read(bus_t* bus, uint16_t addr) {
	return bus->read(addr);
}

void bus_write(bus_t* bus, uint16_t addr, uint8_t val) {
	bus->write(addr, val);
}
