#include "bus.h"
#include "mappers.h"
#include <stdlib.h>

uint8_t bus_read(mapper_t* mapper, uint16_t addr) {
	return mapper->read(addr);
}

void bus_write(bus_t* bus, uint16_t addr, uint8_t val) {
	bus->write(addr, val, bus->mmap);
}
