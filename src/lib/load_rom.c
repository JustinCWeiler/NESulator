#include "load_rom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bus_t* load_rom(const char* filename) {
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		printf("Error: file not found\n");
		exit(-1);
	}

	char magic[4];
	size_t ret = fread(magic, 4, 1, f);
	if (ret != 1) {
		printf("Error reading magic bytes of ROM file\n");
		exit(-1);
	}
	if (magic[0] != 'N' ||
	    magic[1] != 'E' ||
	    magic[2] != 'S' ||
	    magic[3] != 0x1a)  {
		printf("Error: file is not a valid NES ROM\n");
		exit(-1);
	}

	flags_t flags;

	ret = fread(&flags, 4, 1, f);
	if (ret != 1) {
		printf("Error reading flags of ROM file\n");
		exit(-1);
	}

	char* prg_rom = malloc(PRG_CHUNK * flags.prg_size);
	char* chr_rom = malloc(CHR_CHUNK * flags.chr_size);
	if (prg_rom == NULL || chr_rom == NULL) {
		printf("Critical error\n");
		exit(-1);
	}

	fseek(f, 16, SEEK_SET);
	ret = fread(prg_rom, PRG_CHUNK, flags.prg_size, f);
	if (ret != flags.prg_size) {
		printf("Error reading PRG data in ROM file\n");
		exit(-1);
	}
	ret = fread(chr_rom, CHR_CHUNK, flags.chr_size, f);
	if (ret != flags.chr_size) {
		printf("Error reading PRG data in ROM file\n");
		exit(-1);
	}

	return bus_create(flags, prg_rom, chr_rom);
}
