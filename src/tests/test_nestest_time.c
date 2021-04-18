#include "load_rom.h"
#include "cpu.h"
#include "instructions.h"
#include <stdio.h>
#include <time.h>

#include "nestest_include.h"

int main(void) {
	bus_t* bus = load_rom("roms/nestest.nes");
	cpu_t* cpu = cpu_create(bus);

	cpu->reg.PC = 0xC000;

	clock_t start, end;

	printf("Timing pulse now\n");

	start = clock();
	while (cpu->reg.PC != FINAL) {
		cpu_pulse(cpu);
	}
	end = clock();

	printf("Pulse took %fs\n\n", (double)(end - start) / CLOCKS_PER_SEC);

	cpu_reset(cpu);
	cpu->reg.PC = 0xC000;

	printf("Timing execute now\n");

	start = clock();
	while (cpu->reg.PC != FINAL) {
		cpu_execute(cpu);
	}
	end = clock();

	printf("Execute took %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	return 0;
}
