#include "bus.h"
#include <stdlib.h>

typedef struct {
	bus_t bus;
	enum Mirror {
		vertical,
		horizontal,
	} mirror;
} m00_t;
#define ms00 sizeof(m00_t)

void mc00(bus_t* bus) {
}

uint8_t mr00(bus_t* bus, uint16_t addr) {
	return 0;
}

void mw00(bus_t* bus, uint16_t addr, uint8_t val) {
}
