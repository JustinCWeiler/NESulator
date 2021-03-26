#ifndef BUS_H
#define BUS_H

#include <stdint.h>

typedef uint8_t(*read_func)(uint16_t, void*);
typedef void (*write_func)(uint16_t, uint8_t, void*);

typedef struct {
	read_func read;
	write_func write;
	void* data;
} bus_t;

bus_t* bus_create(read_func read, write_func write, void* data);
uint8_t bus_read(bus_t* bus, uint16_t addr);
void bus_write(bus_t* bus, uint16_t addr, uint8_t val);

#endif
