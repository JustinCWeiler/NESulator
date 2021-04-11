#include "mappers.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_DONE 0x01

typedef void (*create_func)(mapper_t*);
typedef uint8_t (*read_func)(mapper_t*, uint16_t);
typedef void (*write_func)(uint16_t, uint8_t);

// array of pointer to create_funcs
// would make typedef but its complicated
create_func create_funcs[] = {
};

read_func read_funcs[] = {
};

write_func write_funcs[] = {
};

mapper_t* create_mapper(uint8_t num, void* prg_rom, uint8_t prg_size,
                                     void* chr_rom, uint8_t chr_size) {
	if (num >= NUM_DONE) {
		printf("Sorry, this game isn't supported yet\n");
		return NULL;
	}

	mapper_t* mapper = malloc(sizeof(mapper_t));

	mapper->num = num;

	mapper->prg_rom = prg_rom;
	mapper->prg_size = prg_size;
	mapper->chr_rom = chr_rom;
	mapper->chr_size = chr_size;

	// TODO: create specific mapper stuff
	// thats it i think idk maybe more

	return mapper;
}
