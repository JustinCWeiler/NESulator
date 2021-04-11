#ifndef MAPPERS_H
#define MAPPERS_H

#include <stdint.h>

#define PRG_CHUNK 0x4000
#define CHR_CHUNK 0x2000

typedef uint8_t (*read_func)(uint16_t);
typedef void (*write_func)(uint16_t, uint8_t);

typedef struct {
	read_func read;
	write_func write;

	uint8_t prg_size;
	uint8_t chr_size;
	void* prg_rom;
	void* chr_rom;
} mapper_t;

mapper_t* create_mapper(uint8_t num, void* prg_rom, void* chr_rom);

#endif
