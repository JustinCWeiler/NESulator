#include "instructions.h"
#include "cpu.h"
#include "bus.h"
#include <stdint.h>

// ---------- ADDRESSING MODES ----------
static uint16_t imp(cpu_t* cpu) {
	(void)cpu;
	return 0;
}

static uint16_t imm(cpu_t* cpu) {
	return cpu->reg.PC++;
}

static uint16_t zpp(cpu_t* cpu) {
	return bus_read(cpu->bus, cpu->reg.PC++);
}

static uint16_t zpx(cpu_t* cpu) {
	return (zpp(cpu) + cpu->reg.X) % 0x100;
}

static uint16_t zpy(cpu_t* cpu) {
	return (zpp(cpu) + cpu->reg.Y) % 0x100;
}

static uint16_t izx(cpu_t* cpu) {
	uint8_t zp = zpx(cpu);
	uint8_t addr_lo = bus_read(cpu->bus, zp);
	uint8_t addr_hi = bus_read(cpu->bus, (zp + 1) % 0x100);

	return (addr_hi << 8) | addr_lo;
}

static uint16_t izy(cpu_t* cpu) {
	uint8_t zp = zpp(cpu);
	uint8_t addr_lo = bus_read(cpu->bus, zp);
	uint8_t addr_hi = bus_read(cpu->bus, (zp + 1) % 0x100);

	uint16_t addr0 = (addr_hi << 8) | addr_lo;
	uint16_t addr1 = addr0 + cpu->reg.Y;

	if ((addr0 & 0xff00) != (addr1 & 0xff00))
		cpu->cycles_left++;

	return addr1;
}

static uint16_t abb(cpu_t* cpu) {
	uint8_t lo = bus_read(cpu->bus, cpu->reg.PC++);
	uint8_t hi = bus_read(cpu->bus, cpu->reg.PC++);

	return (hi << 8) | lo;
}

static uint16_t abx(cpu_t* cpu) {
	uint16_t addr0 = abb(cpu);
	uint16_t addr1 = addr0 + cpu->reg.X;

	if ((addr0 & 0xff00) != (addr1 & 0xff00))
		cpu->cycles_left++;

	return addr1;
}

static uint16_t aby(cpu_t* cpu) {
	uint16_t addr0 = abb(cpu);
	uint16_t addr1 = addr0 + cpu->reg.Y;

	if ((addr0 & 0xff00) != (addr1 & 0xff00))
		cpu->cycles_left++;

	return addr1;
}

static uint16_t ind(cpu_t* cpu) {
	uint16_t ab0 = abb(cpu);
	uint16_t ab1 = ab0 + 1;
	if (!(ab1 & 0xff))
		ab1 -= 0x100;
	uint8_t addr_lo = bus_read(cpu->bus, ab0);
	uint8_t addr_hi = bus_read(cpu->bus, ab1);

	return (addr_hi << 8) | addr_lo;
}

static uint16_t rel(cpu_t* cpu) {
	return imm(cpu);
}

static addr_func addrs[0x100] = {
	imp, izx, imp, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abb, abb, abb, abb,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	abb, izx, imp, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abb, abb, abb, abb,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	imp, izx, imp, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abb, abb, abb, abb,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	imp, izx, imp, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, ind, abb, abb, abb,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	imm, izx, imm, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abb, abb, abb, abb,
	rel, izy, imp, izy, zpx, zpx, zpy, zpy, imp, aby, imp, aby, abx, abx, aby, aby,
	imm, izx, imm, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abb, abb, abb, abb,
	rel, izy, imp, izy, zpx, zpx, zpy, zpy, imp, aby, imp, aby, abx, abx, aby, aby,
	imm, izx, imm, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abb, abb, abb, abb,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	imm, izx, imm, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abb, abb, abb, abb,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
};


// ---------- INSTRUCTIONS ----------

#define PUSH(val) push(cpu, val)
static inline void push(cpu_t* cpu, uint8_t val) {
	bus_write(cpu->bus, STACK_OFFSET + (cpu->reg.S--), val);
}

#define PULL() pull(cpu)
static inline uint8_t pull(cpu_t* cpu) {
	return bus_read(cpu->bus, STACK_OFFSET + (++cpu->reg.S));
}

static void adc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);
	uint8_t oldA = cpu->reg.A;
	uint8_t newA = oldA + get_car(cpu) + val;

	// N, V, Z, C
	clr_neg(cpu);
	clr_ovf(cpu);
	clr_zer(cpu);
	clr_car(cpu);

	if (newA & 0x80)
		set_neg(cpu);
	if ((~(oldA ^ val) & 0x80) && ((oldA ^ newA) & 0x80))
		set_ovf(cpu);
	if (!newA)
		set_zer(cpu);
	if (newA < oldA)
		set_car(cpu);

	cpu->reg.A = newA;
}

static void and(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);
	uint8_t newA = cpu->reg.A & val;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (newA & 0x80)
		set_neg(cpu);
	if (!newA)
		set_zer(cpu);

	cpu->reg.A = newA;
}

static void asl(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val;
	if (addrs[op] == imp)
		val = cpu->reg.A;
	else
		val = bus_read(cpu->bus, addr);

	uint8_t newval = val << 1;

	// N, Z, C
	clr_neg(cpu);
	clr_zer(cpu);
	clr_car(cpu);

	if (newval & 0x80)
		set_neg(cpu);
	if (!newval)
		set_zer(cpu);
	if (val & 0x80)
		set_car(cpu);

	if (addrs[op] == imp)
		cpu->reg.A = newval;
	else
		bus_write(cpu->bus, addr, newval);
}

static void bcc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	if (get_car(cpu) == 0) {
		// must be signed
		int8_t val = bus_read(cpu->bus, addr);
		cpu->reg.PC += val;
		cpu->cycles_left++;
	}
}

static void bcs(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	if (get_car(cpu) == 1) {
		// must be signed
		int8_t val = bus_read(cpu->bus, addr);
		cpu->reg.PC += val;
		cpu->cycles_left++;
	}
}

static void beq(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	if (get_zer(cpu) == 1) {
		// must be signed
		int8_t val = bus_read(cpu->bus, addr);
		cpu->reg.PC += val;
		cpu->cycles_left++;
	}
}

static void bit(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);

	// N, V, Z
	clr_neg(cpu);
	clr_ovf(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (val & 0x40)
		set_ovf(cpu);
	if (!(cpu->reg.A & val))
		set_zer(cpu);
}

static void bmi(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	if (get_neg(cpu) == 1) {
		// must be signed
		int8_t val = bus_read(cpu->bus, addr);
		cpu->reg.PC += val;
		cpu->cycles_left++;
	}
}

static void bne(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	if (get_zer(cpu) == 0) {
		// must be signed
		int8_t val = bus_read(cpu->bus, addr);
		cpu->reg.PC += val;
		cpu->cycles_left++;
	}
}

static void bpl(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	if (get_neg(cpu) == 0) {
		// must be signed
		int8_t val = bus_read(cpu->bus, addr);
		cpu->reg.PC += val;
		cpu->cycles_left++;
	}
}

static void brk(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t pc_hi = cpu->reg.PC >> 8;
	uint8_t pc_lo = cpu->reg.PC & 0xf;

	// push values to stack
	PUSH(pc_hi);
	PUSH(pc_lo);
	PUSH(cpu->reg.P);

	// set flags
	set_brk(cpu);
	set_ida(cpu);

	// change PC
	pc_lo = bus_read(cpu->bus, BRK_VECTOR_LO);
	pc_hi = bus_read(cpu->bus, BRK_VECTOR_HI);

	cpu->reg.PC = (pc_hi << 8) | pc_lo;
}

static void bvc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	if (get_ovf(cpu) == 0) {
		// must be signed
		int8_t val = bus_read(cpu->bus, addr);
		cpu->reg.PC += val;
		cpu->cycles_left++;
	}
}

static void bvs(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	if (get_ovf(cpu) == 1) {
		// must be signed
		int8_t val = bus_read(cpu->bus, addr);
		cpu->reg.PC += val;
		cpu->cycles_left++;
	}
}

static void clc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	clr_car(cpu);
}

static void cld(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	clr_dec(cpu);
}

static void cli(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	clr_ida(cpu);
}

static void clv(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	clr_ovf(cpu);
}

static void cmp(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);
	uint8_t res = cpu->reg.A - val;

	// N, Z, C
	clr_neg(cpu);
	clr_zer(cpu);
	clr_car(cpu);

	if (res & 0x80)
		set_neg(cpu);
	if (!res)
		set_zer(cpu);
	if (cpu->reg.A >= val)
		set_car(cpu);
}

static void cpx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);
	uint8_t res = cpu->reg.X - val;

	// N, Z, C
	clr_neg(cpu);
	clr_zer(cpu);
	clr_car(cpu);

	if (res & 0x80)
		set_neg(cpu);
	if (!res)
		set_zer(cpu);
	if (cpu->reg.X >= val)
		set_car(cpu);
}

static void cpy(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);
	uint8_t res = cpu->reg.Y - val;

	// N, Z, C
	clr_neg(cpu);
	clr_zer(cpu);
	clr_car(cpu);

	if (res & 0x80)
		set_neg(cpu);
	if (!res)
		set_zer(cpu);
	if (cpu->reg.Y >= val)
		set_car(cpu);
}

static void dec(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);
	val--;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	bus_write(cpu->bus, addr, val);
}

static void dex(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	cpu->reg.X--;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (cpu->reg.X & 0x80)
		set_neg(cpu);
	if (!cpu->reg.X)
		set_zer(cpu);
}

static void dey(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	cpu->reg.Y--;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (cpu->reg.Y & 0x80)
		set_neg(cpu);
	if (!cpu->reg.Y)
		set_zer(cpu);
}

static void eor(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);
	uint8_t newA = cpu->reg.A ^ val;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (newA & 0x80)
		set_neg(cpu);
	if (!newA)
		set_zer(cpu);

	cpu->reg.A = newA;
}

static void inc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);
	val++;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	bus_write(cpu->bus, addr, val);
}

static void inx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	cpu->reg.X++;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (cpu->reg.X & 0x80)
		set_neg(cpu);
	if (!cpu->reg.X)
		set_zer(cpu);
}

static void iny(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	cpu->reg.Y++;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (cpu->reg.Y & 0x80)
		set_neg(cpu);
	if (!cpu->reg.Y)
		set_zer(cpu);
}

static void jmp(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	cpu->reg.PC = addr;
}

static void jsr(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t pc_hi = (cpu->reg.PC - 1) >> 8;
	uint8_t pc_lo = (cpu->reg.PC - 1) & 0xff;

	PUSH(pc_hi);
	PUSH(pc_lo);

	cpu->reg.PC = addr;
}

static void lda(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	cpu->reg.A = val;
}

static void ldx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	cpu->reg.X = val;
}

static void ldy(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	cpu->reg.Y = val;
}

static void lsr(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val;
	if (addrs[op] == imp)
		val = cpu->reg.A;
	else
		val = bus_read(cpu->bus, addr);

	uint8_t newval = val >> 1;

	// N, Z, C
	clr_neg(cpu);
	clr_zer(cpu);
	clr_car(cpu);

	if (newval & 0x80)
		set_neg(cpu);
	if (!newval)
		set_zer(cpu);
	if (val & 0x1)
		set_car(cpu);

	if (addrs[op] == imp)
		cpu->reg.A = newval;
	else
		bus_write(cpu->bus, addr, newval);
}

static void nop(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;
}

static void ora(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = bus_read(cpu->bus, addr);
	uint8_t newA = cpu->reg.A | val;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (newA & 0x80)
		set_neg(cpu);
	if (!newA)
		set_zer(cpu);

	cpu->reg.A = newA;
}

static void pha(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	PUSH(cpu->reg.A);
}

static void php(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	PUSH(cpu->reg.P);
}

static void pla(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = PULL();

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	cpu->reg.A = val;
}

static void plp(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	cpu->reg.P = PULL();
}

static void rol(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val;
	if (addrs[op] == imp)
		val = cpu->reg.A;
	else
		val = bus_read(cpu->bus, addr);

	uint8_t newval = (val << 1) + get_car(cpu);

	// N, Z, C
	clr_neg(cpu);
	clr_zer(cpu);
	clr_car(cpu);

	if (newval & 0x80)
		set_neg(cpu);
	if (!newval)
		set_zer(cpu);
	if (val & 0x80)
		set_car(cpu);

	if (addrs[op] == imp)
		cpu->reg.A = newval;
	else
		bus_write(cpu->bus, addr, newval);
}

static void ror(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val;
	if (addrs[op] == imp)
		val = cpu->reg.A;
	else
		val = bus_read(cpu->bus, addr);

	uint8_t newval = (val >> 1) + (get_car(cpu) << 7);

	// N, Z, C
	clr_neg(cpu);
	clr_zer(cpu);
	clr_car(cpu);

	if (newval & 0x80)
		set_neg(cpu);
	if (!newval)
		set_zer(cpu);
	if (val & 0x1)
		set_car(cpu);

	if (addrs[op] == imp)
		cpu->reg.A = newval;
	else
		bus_write(cpu->bus, addr, newval);
}

static void rti(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	cpu->reg.P = PULL();
	uint8_t pc_lo = PULL();
	uint8_t pc_hi = PULL();

	cpu->reg.PC = (pc_hi << 8) | pc_lo;
}

static void rts(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t pc_lo = PULL();
	uint8_t pc_hi = PULL();

	cpu->reg.PC = ((pc_hi << 8) | pc_lo) + 1;
}

static void sbc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = ~bus_read(cpu->bus, addr);
	uint8_t oldA = cpu->reg.A;
	uint8_t newA = oldA + get_car(cpu) + val;

	// N, V, Z, C
	clr_neg(cpu);
	clr_ovf(cpu);
	clr_zer(cpu);
	clr_car(cpu);

	if (newA & 0x80)
		set_neg(cpu);
	if ((~(oldA ^ val) & 0x80) && ((oldA ^ newA) & 0x80))
		set_ovf(cpu);
	if (!newA)
		set_zer(cpu);
	if (newA < oldA)
		set_car(cpu);

	cpu->reg.A = newA;
}

static void sec(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	set_car(cpu);
}

static void sed(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	set_dec(cpu);
}

static void sei(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	set_ida(cpu);
}

static void sta(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	bus_write(cpu->bus, addr, cpu->reg.A);
}

static void stx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	bus_write(cpu->bus, addr, cpu->reg.X);
}

static void sty(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	bus_write(cpu->bus, addr, cpu->reg.Y);
}

static void tax(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = cpu->reg.A;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	cpu->reg.X = val;
}

static void tay(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = cpu->reg.A;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	cpu->reg.Y = val;
}

static void tsx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = cpu->reg.S;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	cpu->reg.X = val;
}

static void txa(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = cpu->reg.X;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	cpu->reg.A = val;
}

static void txs(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = cpu->reg.X;

	cpu->reg.S = val;
}

static void tya(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;

	uint8_t val = cpu->reg.Y;

	// N, Z
	clr_neg(cpu);
	clr_zer(cpu);

	if (val & 0x80)
		set_neg(cpu);
	if (!val)
		set_zer(cpu);

	cpu->reg.A = val;
}

// Implementation of illegal opcodes

static void lax(cpu_t* cpu, uint8_t op, uint16_t addr) {
	lda(cpu, op, addr);
	tax(cpu, op, addr);
}

static void ill(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)op;
	(void)cpu;
	(void)addr;
}

static inst_func inst[0x100] = {
	brk, ora, ill, ill, nop, ora, asl, ill, php, ora, asl, ill, nop, ora, asl, ill,
	bpl, ora, ill, ill, nop, ora, asl, ill, clc, ora, nop, ill, nop, ora, asl, ill,
	jsr, and, ill, ill, bit, and, rol, ill, plp, and, rol, ill, bit, and, rol, ill,
	bmi, and, ill, ill, nop, and, rol, ill, sec, and, nop, ill, nop, and, rol, ill,
	rti, eor, ill, ill, nop, eor, lsr, ill, pha, eor, lsr, ill, jmp, eor, lsr, ill,
	bvc, eor, ill, ill, nop, eor, lsr, ill, cli, eor, nop, ill, nop, eor, lsr, ill,
	rts, adc, ill, ill, nop, adc, ror, ill, pla, adc, ror, ill, jmp, adc, ror, ill,
	bvs, adc, ill, ill, nop, adc, ror, ill, sei, adc, nop, ill, nop, adc, ror, ill,
	nop, sta, nop, ill, sty, sta, stx, ill, dey, ill, txa, ill, sty, sta, stx, ill,
	bcc, sta, ill, ill, sty, sta, stx, ill, tya, sta, txs, ill, ill, sta, ill, ill,
	ldy, lda, ldx, lax, ldy, lda, ldx, ill, tay, lda, tax, ill, ldy, lda, ldx, ill,
	bcs, lda, ill, ill, ldy, lda, ldx, ill, clv, lda, tsx, ill, ldy, lda, ldx, ill,
	cpy, cmp, nop, ill, cpy, cmp, dec, ill, iny, cmp, dex, ill, cpy, cmp, dec, ill,
	bne, cmp, ill, ill, nop, cmp, dec, ill, cld, cmp, nop, ill, nop, cmp, dec, ill,
	cpx, sbc, nop, ill, cpx, sbc, inc, ill, inx, sbc, nop, ill, cpx, sbc, inc, ill,
	beq, sbc, ill, ill, nop, sbc, inc, ill, sed, sbc, nop, ill, nop, sbc, inc, ill
};


// ---------- CYCLE COUNTS ----------
static uint8_t cycles[0x100] = {
	7, 6, 1, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6,
	2, 5, 1, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	6, 6, 1, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6,
	2, 5, 1, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	6, 6, 1, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6,
	2, 5, 1, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	6, 6, 1, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6,
	2, 5, 1, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
	2, 6, 1, 6, 4, 4, 4, 4, 2, 5, 2, 5, 5, 5, 5, 5,
	2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
	2, 5, 1, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4,
	2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
	2, 5, 1, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
	2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
	2, 5, 1, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7
};


// ---------- FUNCTIONS ----------
uint16_t get_addr(cpu_t* cpu, uint8_t op) { return addrs[op](cpu); }
void execute_instruction(cpu_t* cpu, uint8_t op, uint16_t addr) { return inst[op](cpu, op, addr); }

uint8_t get_base_cycles(uint8_t op) { return cycles[op]; }
