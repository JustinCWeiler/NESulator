#include "mappers.h"
#include <stdlib.h>

static uint16_t mirror(uint16_t addr) {
	if (addr <= 0x1fff)
		return addr % 0x800;
	if (0x2000 <= addr && addr <= 0x3fff)
		return 0x2000 + (addr % 8);
	return addr;
}

static uint16_t ma00(uint16_t addr, m00_t* mmap) {
	addr = mirror(addr);

	// prg ram
	if (mmap->prg_ram_size != 0 && 0x6000 <= addr && addr <= 0x7fff)
		return 0x6000 + (addr % (mmap->prg_ram_size*0x800));
	// prg rom
	if (0x8000 <= addr)
		return 0x8000 + (addr % (mmap->prg_rom_size*0x4000));

	return addr;
}

static uint8_t mr00(uint16_t addr, void* data) {
	m00_t* mmap = data;
	addr = ma00(addr, mmap);

	return mmap->cpu_mem[addr];
}

static void mw00(uint16_t addr, uint8_t val, void* data) {
	m00_t* mmap = data;
	addr = ma00(addr, mmap);

	mmap->cpu_mem[addr] = val;
}

read_func read_funcs[] = {
	mr00
};

write_func write_funcs[] = {
	mw00
};
