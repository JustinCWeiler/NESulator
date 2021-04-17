#include "load_rom.h"
#include "flags.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bus_t* load_rom(const char* filename) {
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		printf("Error: file not found\n");
		exit(-1);
	}

	char magic[4];
	fread(magic, 4, 1, f);
	if (magic[0] != 'N' ||
	    magic[1] != 'E' ||
	    magic[2] != 'S' ||
	    magic[3] != 0x1a)  {
		printf("Error: file is not a valid NES ROM\n");
		exit(-1);
	}

	flags_t flags;

	fread(&flags, 4, 1, f);

	char* prg_rom = malloc(PRG_CHUNK * flags.prg_size);
	char* chr_rom = malloc(CHR_CHUNK * flags.chr_size);
	if (prg_rom == NULL || chr_rom == NULL) {
		printf("Critical error\n");
		exit(-1);
	}

	fseek(f, 16, SEEK_SET);
	fread(prg_rom, PRG_CHUNK, flags.prg_size, f);
	fread(chr_rom, CHR_CHUNK, flags.chr_size, f);

	return bus_create(flags, prg_rom, chr_rom);
}
