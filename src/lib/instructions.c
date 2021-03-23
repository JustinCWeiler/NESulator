#include "instructions.h"
#include "cpu.h"

// ---------- ADDRESSING MODES ----------
static uint16_t imp(cpu_t* cpu) {
	(void)cpu;
	return 0;
}

static uint16_t imm(cpu_t* cpu) {
	return cpu->reg.PC++;
}

static uint16_t zpp(cpu_t* cpu) {
	return cpu->bus->read(cpu->reg.PC++);
}

static uint16_t zpx(cpu_t* cpu) {
	return (zpp(cpu) + cpu->reg.X) % 0x100;
}

static uint16_t zpy(cpu_t* cpu) {
	return (zpp(cpu) + cpu->reg.Y) % 0x100;
}

static uint16_t izx(cpu_t* cpu) {
	return cpu->bus->read(zpx(cpu));
}

static uint16_t izy(cpu_t* cpu) {
	uint16_t addr0 = cpu->bus->read(zpp(cpu));
	uint16_t addr1 = addr0 + cpu->reg.Y;

	if ((addr0 & 0xff00) != (addr1 & 0xff00))
		cpu->cycles_left++;

	return addr1;
}

static uint16_t abs(cpu_t* cpu) {
	uint8_t lo = cpu->bus->read(cpu->reg.PC++);
	uint8_t hi = cpu->bus->read(cpu->reg.PC++);

	return (hi << 8) | lo;
}

static uint16_t abx(cpu_t* cpu) {
	uint16_t addr0 = abs(cpu);
	uint16_t addr1 = addr0 + cpu->reg.X;

	if ((addr0 & 0xff00) != (addr1 & 0xff00))
		cpu->cycles_left++;

	return addr1;
}

static uint16_t aby(cpu_t* cpu) {
	uint16_t addr0 = abs(cpu);
	uint16_t addr1 = addr0 + cpu->reg.Y;

	if ((addr0 & 0xff00) != (addr1 & 0xff00))
		cpu->cycles_left++;

	return addr1;
}

static uint16_t ind(cpu_t* cpu) {
	return cpu->bus->read(abs(cpu));
}

static uint16_t rel(cpu_t* cpu) {
	return abs(cpu);
}

static addr_func addr[0x100] = {
	imp, izx, imp, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abs, abs, abs, abs,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	abs, izx, imp, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abs, abs, abs, abs,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	imp, izx, imp, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abs, abs, abs, abs,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	imp, izx, imp, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, ind, abs, abs, abs,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	imm, izx, imm, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abs, abs, abs, abs,
	rel, izy, imp, izy, zpx, zpx, zpy, zpy, imp, aby, imp, aby, abx, abx, aby, aby,
	imm, izx, imm, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abs, abs, abs, abs,
	rel, izy, imp, izy, zpx, zpx, zpy, zpy, imp, aby, imp, aby, abx, abx, aby, aby,
	imm, izx, imm, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abs, abs, abs, abs,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
	imm, izx, imm, izx, zpp, zpp, zpp, zpp, imp, imm, imp, imm, abs, abs, abs, abs,
	rel, izy, imp, izy, zpx, zpx, zpx, zpx, imp, aby, imp, aby, abx, abx, abx, abx,
};


// ---------- INSTRUCTIONS ----------
static void adc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void and(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void asl(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void bcc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void bcs(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void beq(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void bit(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void bmi(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void bne(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void bpl(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void brk(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void bvc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void bvs(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void clc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void cld(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void cli(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void clv(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void cmp(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void cpx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void cpy(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void dec(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void dex(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void dey(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void eor(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void inc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void inx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void iny(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void jmp(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void jsr(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void lda(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void ldx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void ldy(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void lsr(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void nop(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void ora(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void pha(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void php(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void pla(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void plp(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void rol(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void ror(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void rti(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void rts(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void sbc(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void sec(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void sed(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void sei(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void sta(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void stx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void sty(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void tax(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void tay(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void tsx(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void txa(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void txs(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void tya(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
	(void)addr;
}

static void ill(cpu_t* cpu, uint8_t op, uint16_t addr) {
	(void)cpu;
	(void)op;
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
	ldy, lda, ldx, ill, ldy, lda, ldx, ill, tay, lda, tax, ill, ldy, lda, ldx, ill,
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
uint16_t get_addr(cpu_t* cpu, uint8_t op) { return addr[op](cpu); }
void execute_instruction(cpu_t* cpu, uint8_t op, uint16_t addr) { return inst[op](cpu, op, addr); }

uint8_t get_base_cycles(uint8_t op) { return cycles[op]; }
