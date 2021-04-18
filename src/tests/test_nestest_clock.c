#include "load_rom.h"
#include "cpu.h"
#include "instructions.h"
#include <stdio.h>

#include "nestest_include.h"

int main(void) {
	bus_t* bus = load_rom("roms/nestest.nes");
	cpu_t* cpu = cpu_create(bus);

	cpu->reg.PC = 0xC000;

	size_t c = 7;
	size_t i = 0;
	while (i < MAX) {
		if (cpu->cycles_left == 0) {
			if (c != cycles[i]) {
				printf("ERROR:\ncpu cycles: %lu\nactual cycles: %lu\n", c, cycles[i]);
				return -1;
			}
			i++;
		}

		cpu_pulse(cpu);
		c++;
	}
	
	return 0;
}
