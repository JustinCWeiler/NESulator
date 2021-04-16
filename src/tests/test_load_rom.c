#include "load_rom.h"
#include <stdio.h>

static unsigned int failed = 0;

int main(void) {
	printf("START TESTS\n");

	load_rom("./roms/nestest.nes");

	printf("END TESTS\n\n");

	printf("Failed %u tests\n", failed);

	return 0;
}
