#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>

typedef struct {
	uint8_t prg_size;	// byte 4
	uint8_t chr_size;	// byte 5
	// flags 6
	uint8_t mirror:1;	// byte 6
	uint8_t prg_ram:1;
	uint8_t trainer:1;
	uint8_t four_vram:1;
	uint8_t map_lo:4;
	// flags 7
	uint8_t vs:1;		// byte 7
	uint8_t pc10:1;
	uint8_t nes2:2;
	uint8_t map_hi:4;
} flags_t;

#endif
