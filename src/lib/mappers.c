#include "mappers.h"
#include <stdint.h>
#include <stdio.h>

#define NUM_DONE 0x01

read_func read_funcs[] = {
};

write_func write_funcs[] = {
};

mapper_t* create_mapper(uint8_t num, void* prg_rom, void* chr_rom) {
	if (num >= NUM_DONE) {
		printf("Sorry, this game isn't supported yet\n");
		return NULL;
	}
}
