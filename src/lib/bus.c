#include "bus.h"
#include <stdlib.h>

bus_t* bus_create(read_func read, write_func write) {
	bus_t* bus = malloc(sizeof(bus_t));

	bus->read = read;
	bus->write = write;

	return bus;
}
