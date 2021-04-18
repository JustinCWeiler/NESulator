#include "load_rom.h"
#include "cpu.h"
#include <stdio.h>
#include <stdbool.h>

#include "nestest_include.h"

int main(void) {
	bus_t* bus = load_rom("roms/nestest.nes");
	cpu_t* cpu = cpu_create(bus);

	cpu->reg.PC = 0xC000;

	for (size_t i = 0; i < MAX; i++) {
		bool failed = false;
		if (cpu->reg.PC != pc[i]) {
			printf("ERROR:\nCPU pc: 0x%04X\nActual pc: 0x%04X\n", cpu->reg.PC, pc[i]);
			failed = true;
		}
		if (cpu->reg.A != a[i]) {
			printf("ERROR:\nCPU a: 0x%02X\nActual a: 0x%02X\n", cpu->reg.A, a[i]);
			failed = true;
		}
		if (cpu->reg.X != x[i]) {
			printf("ERROR:\nCPU x: 0x%02X\nActual x: 0x%02X\n", cpu->reg.X, x[i]);
			failed = true;
		}
		if (cpu->reg.Y != y[i]) {
			printf("ERROR:\nCPU y: 0x%02X\nActual y: 0x%02X\n", cpu->reg.Y, y[i]);
			failed = true;
		}
		if (cpu->reg.P != p[i]) {
			printf("ERROR:\nCPU p: 0x%02X\nActual p: 0x%02X\n", cpu->reg.P, p[i]);
			failed = true;
		}
		if (cpu->reg.S != s[i]) {
			printf("ERROR:\nCPU s: 0x%02X\nActual s: 0x%02X\n", cpu->reg.S, s[i]);
			failed = true;
		}

		if (failed) {
			printf("Actual pc: 0x%04X\n", pc[i]);
			return -1;
		}

		cpu_execute(cpu);
	}

	printf("Ending execution\n");

	printf("Testing memory values\n");

	uint8_t val;
	if ((val = bus_read(cpu->bus, 0x02)) != 0)
		printf("In byte 0x02 we have 0x%02X\n", val);
	if ((val = bus_read(cpu->bus, 0x03)) != 0)
		printf("In byte 0x03 we have 0x%02X\n", val);

	return 0;
}
