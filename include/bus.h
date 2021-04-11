#ifndef BUS_H
#define BUS_H

#include "mappers.h"
#include <stdint.h>

typedef struct {
	mapper_t* mapper;
} bus_t;

uint8_t bus_read(mapper_t* mapper, uint16_t addr);
void bus_write(mapper_t* mapper, uint16_t addr, uint8_t val);

#endif
