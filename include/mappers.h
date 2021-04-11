#ifndef MAPPERS_H
#define MAPPERS_H

#include <stdint.h>

#define PRG_CHUNK 0x4000
#define CHR_CHUNK 0x2000

typedef struct {
	uint8_t num;
	void* prg_rom;
	uint8_t prg_size;
	void* chr_rom;
	uint8_t chr_size;
} mapper_t;

mapper_t* create_mapper(uint8_t num, void* prg_rom, uint8_t prg_size,
                                     void* chr_rom, uint8_t chr_size);

uint8_t read(mapper_t* mapper, uint16_t addr);
void write(mapper_t* mapper, uint16_t addr, uint8_t val);

#endif
