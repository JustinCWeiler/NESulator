#include "cpu.h"
#include "bus.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define START 0x8000
#define START_LO (START&0xf)
#define START_HI (START>>8);

static uint8_t memory[0x10000];

static uint8_t read(uint16_t addr) { return memory[addr]; }
static void write(uint16_t addr, uint8_t val) { memory[addr] = val; }

static const unsigned char ADD_PRG[] = {
	0xA9, 0x69, 0x18, 0x69, 0x42, 0x8D, 0x00, 0x00,
	0x02
};

static const unsigned char MULT_PRG[] = {
	0xA9, 0x69, 0x8D, 0x00, 0x00, 0xA9, 0x42, 0xAA,
	0xA9, 0x00, 0x18, 0x6D, 0x00, 0x00, 0xCA, 0xD0,
	0xF9, 0x8D, 0x00, 0x00, 0x02
};

static const unsigned char ALT_MULT_PRG[] = {
	0xA9, 0x69, 0x8D, 0x00, 0x00, 0xA9, 0x42, 0xAA,
	0xA9, 0x00, 0x6D, 0x00, 0x00, 0xCA, 0xD0, 0xFA,
	0x8D, 0x00, 0x00, 0x02
};


static unsigned int failed = 0;

void test_reset_cpu(cpu_t* cpu) {
	printf("test_reset_prg\n");
	cpu_reset(cpu);

	if (cpu->reg.PC != START) {
		printf("FAILED: cpu reset\n");
		failed++;
	}
}

void test_add_prg(cpu_t* cpu) {
	printf("test_add_prg\n");

	cpu_reset(cpu);
	memcpy(&memory[START], ADD_PRG, sizeof(ADD_PRG));

	unsigned int count = 0;
	while (cpu->bus->read(cpu->reg.PC) != 0x02 || cpu->cycles_left != 0) {
		cpu_pulse(cpu);
		count++;
	}

	if (count != 10) {
		printf("FAILED: add prg count\n");
		failed++;
	}

	if (memory[0] != 0xab) {
		printf("FAILED: add prg memory\n");
		failed++;
	}
}

void test_mult_prg(cpu_t* cpu) {
	printf("test_mult_prg\n");

	cpu_reset(cpu);
	memcpy(&memory[START], MULT_PRG, sizeof(MULT_PRG));

	unsigned int count = 0;
	while (cpu->bus->read(cpu->reg.PC) != 0x02 || cpu->cycles_left != 0) {
		cpu_pulse(cpu);
		count++;
	}

	if (count != 741) {
		printf("FAILED: mult prg count - %u\n", count);
		failed++;
	}

	if (memory[0] != 0x12) {
		printf("FAILED: mult prg memory\n");
		failed++;
	}
}

void test_alt_mult_prg(cpu_t* cpu) {
	printf("test_alt_mult_prg\n");

	cpu_reset(cpu);
	memcpy(&memory[START], ALT_MULT_PRG, sizeof(ALT_MULT_PRG));

	unsigned int count = 0;
	while (cpu->bus->read(cpu->reg.PC) != 0x02 || cpu->cycles_left != 0) {
		cpu_pulse(cpu);
		count++;
	}

	if (count != 609) {
		printf("FAILED: alt mult prg count\n");
		failed++;
	}

	if (memory[0] != 0x2c) {
		printf("FAILED: alt mult prg memory\n");
		failed++;
	}
}

int main(void) {
	bus_t bus = { read, write };
	cpu_t* cpu = cpu_create(&bus);

	memory[RESET_VECTOR_LO] = START_LO;
	memory[RESET_VECTOR_HI] = START_HI;

	printf("START TESTS\n");

	test_reset_cpu(cpu);
	test_add_prg(cpu);
	test_mult_prg(cpu);
	//test_alt_mult_prg(cpu);

	printf("END TESTS\n\n");

	printf("Failed %u tests\n", failed);

	return 0;
}
