#include "bus.h"
#include <string.h>

// ---------- MAPPER 0x00 ----------

typedef struct {
	bus_t bus;
	enum Mirroring {
		horizontal,
		vertical,
	} mirroring;
} m00_t;
#define ms00 sizeof(m00_t)

static char* ma00(bus_t* bus, uint16_t addr) {
	const int PRG_BASE = 0x8000;

	addr = addr_wrap(addr);

	if (bus->flags.prg_size < 2 && PRG_BASE + PRG_CHUNK <= addr)
		addr -= PRG_CHUNK;
	if (PRG_BASE <= addr)
		return bus->prg_rom + addr - PRG_BASE;

	return bus->cpu_mem + addr;
}

void mc00(bus_t* bus) {
	m00_t* m = (m00_t*)bus;

	m->mirroring = bus->flags.mirroring;
}

uint8_t mr00(bus_t* bus, uint16_t addr) {
	return *ma00(bus, addr);
}

void mw00(bus_t* bus, uint16_t addr, uint8_t val) {
	if (0x4020 <= addr)
		return;
	*ma00(bus, addr) = val;
}

// ---------- MAPPER 0x01 ----------

// ---------- MAPPER 0x02 ----------

// ---------- MAPPER 0x03 ----------

// ---------- MAPPER 0x04 ----------

// ---------- MAPPER 0x05 ----------

// ---------- MAPPER 0x06 ----------

// ---------- MAPPER 0x07 ----------
