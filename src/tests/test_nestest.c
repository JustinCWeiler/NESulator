#include "load_rom.h"
#include "cpu.h"
#include <stdio.h>

#include "nestest_pc.c"

int main(void) {
	bus_t* bus = load_rom("roms/nestest.nes");
	cpu_t* cpu = cpu_create(bus);

	cpu->reg.PC = 0xC000;

	size_t max = sizeof(pc)/sizeof(uint16_t);
	for (size_t i = 0; i < max; i++) {
		if (cpu->reg.PC != pc[i]) {
			printf("ERROR:\nCPU pc: 0x%04X\nActual pc: 0x%04X\n", cpu->reg.PC, pc[i]);
			return -1;
		}
		cpu_execute(cpu);
	}

	printf("Ending execution\n");

	return 0;
}
