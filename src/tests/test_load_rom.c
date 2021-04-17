#include "load_rom.h"
#include <stdio.h>
#include <stdbool.h>

#include "nestest_snippets.c"

static unsigned int failed = 0;

void test_flags(bus_t* bus) {
	flags_t flags = bus->flags;

	if (flags.prg_size != 1) {
		printf("flags: prg_size\n");
		failed++;
	}
	if (flags.chr_size != 1) {
		printf("flags: chr_size\n");
		failed++;
	}
	if (flags.mirroring != 0) {
		printf("flags: mirroring\n");
		failed++;
	}
	if (flags.prg_ram != 0) {
		printf("flags: prg_ram\n");
		failed++;
	}
	if (flags.trainer != 1) {
		printf("flags: trainer\n");
		failed++;
	}
	if (flags.four_vram != 1) {
		printf("flags: four_vram\n");
		failed++;
	}
	if (flags.map_lo != 0) {
		printf("flags: mapp_lo\n");
		failed++;
	}
	if (flags.vs != 1) {
		printf("flags: vs\n");
		failed++;
	}
	if (flags.pc10 != 1) {
		printf("flags: pc10\n");
		failed++;
	}
	if (flags.nes2 != 2) {
		printf("flags: nes2\n");
		failed++;
	}
	if (flags.map_hi != 0) {
		printf("flags: map_hi\n");
		failed++;
	}
}

void test_begin_prg(bus_t* bus) {
	for (int i = 0; i < CHUNK; i++) {
		if (bus->prg_rom[i] != prg_begin[i]) {
			printf("test_begin_prg\n");
			failed++;
			return;
		}
	}
}

#define PRG_END_START (0x4000-CHUNK)

void test_end_prg(bus_t* bus) {
	for (int i = 0; i < CHUNK; i++) {
		if (bus->prg_rom[i + PRG_END_START] != prg_end[i]) {
			printf("test_end_prg\n");
			failed++;
			return;
		}
	}
}

void test_begin_chr(bus_t* bus) {
	for (int i = 0; i < CHUNK; i++) {
		if (bus->chr_rom[i] != chr_begin[i]) {
			printf("test_begin_chr\n");
			failed++;
			return;
		}
	}
}

#define CHR_END_START (0x2000-CHUNK)

void test_end_chr(bus_t* bus) {
	for (int i = 0; i < CHUNK; i++) {
		if (bus->chr_rom[i + CHR_END_START] != chr_end[i]) {
			printf("test_end_chr\n");
			failed++;
			return;
		}
	}
}

int main(void) {
	bus_t* bus = load_rom("roms/nestest_fake.nes");

	printf("START TESTS\n");

	test_flags(bus);
	test_begin_prg(bus);
	test_end_prg(bus);
	test_begin_chr(bus);
	test_end_chr(bus);

	printf("END TESTS\n\n");

	printf("Failed %u tests\n", failed);

	return 0;
}
