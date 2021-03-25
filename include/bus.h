#ifndef BUS_H
#define BUS_H

#include <stdint.h>

typedef uint8_t(*read_func)(uint16_t);
typedef void (*write_func)(uint16_t, uint8_t);

typedef struct {
	read_func read;
	write_func write;
} bus_t;

bus_t* bus_create(read_func read, write_func write);

#endif
