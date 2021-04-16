#include "bus.h"

// ---------- MAPPER 0x00 ----------

typedef struct {
	bus_t bus;
	enum Mirroring {
		horizontal,
		vertical,
	} mirroring;
} m00_t;
#define ms00 sizeof(m00_t)

static uint16_t ma00(bus_t* bus, uint16_t addr) {
	addr = addr_wrap(addr);

	if (bus->flags.prg_size < 2 && 0xc000 <= addr)
		return addr - 0x2000;

	return addr;
}

void mc00(bus_t* bus) {
	m00_t* m = (m00_t*)bus;
	m->mirroring = bus->flags.mirroring;
}

uint8_t mr00(bus_t* bus, uint16_t addr) {
	addr = ma00(bus, addr);

	return bus->cpu_mem[addr];
}

void mw00(bus_t* bus, uint16_t addr, uint8_t val) {
	addr = ma00(bus, addr);

	bus->cpu_mem[addr] = val;
}

// ---------- MAPPER 0x01 ----------

// ---------- MAPPER 0x02 ----------

// ---------- MAPPER 0x03 ----------

// ---------- MAPPER 0x04 ----------

// ---------- MAPPER 0x05 ----------

// ---------- MAPPER 0x06 ----------

// ---------- MAPPER 0x07 ----------
