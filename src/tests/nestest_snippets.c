#define CHUNK 0x80

char prg_begin[] = {
	0x4c, 0xf5, 0xc5, 0x60, 0x78, 0xd8, 0xa2, 0xff,
	0x9a, 0xad, 0x02, 0x20, 0x10, 0xfb, 0xad, 0x02,
	0x20, 0x10, 0xfb, 0xa9, 0x00, 0x8d, 0x00, 0x20,
	0x8d, 0x01, 0x20, 0x8d, 0x05, 0x20, 0x8d, 0x05,
	0x20, 0xad, 0x02, 0x20, 0xa2, 0x20, 0x8e, 0x06,
	0x20, 0xa2, 0x00, 0x8e, 0x06, 0x20, 0xa2, 0x00,
	0xa0, 0x0f, 0xa9, 0x00, 0x8d, 0x07, 0x20, 0xca,
	0xd0, 0xfa, 0x88, 0xd0, 0xf7, 0xa9, 0x3f, 0x8d,
	0x06, 0x20, 0xa9, 0x00, 0x8d, 0x06, 0x20, 0xa2,
	0x00, 0xbd, 0x78, 0xff, 0x8d, 0x07, 0x20, 0xe8,
	0xe0, 0x20, 0xd0, 0xf5, 0xa9, 0xc0, 0x8d, 0x17,
	0x40, 0xa9, 0x00, 0x8d, 0x15, 0x40, 0xa9, 0x78,
	0x85, 0xd0, 0xa9, 0xfb, 0x85, 0xd1, 0xa9, 0x7f,
	0x85, 0xd3, 0xa0, 0x00, 0x8c, 0x06, 0x20, 0x8c,
	0x06, 0x20, 0xa9, 0x00, 0x85, 0xd7, 0xa9, 0x07,
	0x85, 0xd0, 0xa9, 0xc3, 0x85, 0xd1, 0x20, 0xa7,
};

char prg_end[] = {
	0x38, 0x06, 0x12, 0x33, 0x3a, 0x06, 0x12, 0x33,
	0x0f, 0x06, 0x12, 0x33, 0x33, 0x06, 0x12, 0x33,
	0x38, 0x06, 0x12, 0x33, 0x3a, 0x06, 0x12, 0x33,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xaf, 0xc5, 0x04, 0xc0, 0xf4, 0xc5,
};

char chr_begin[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x80, 0xff, 0x80, 0x80, 0x00, 0x00, 0x00,
	0x80, 0x80, 0xff, 0x80, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x01, 0xff, 0x01, 0x01, 0x00, 0x00, 0x00,
	0x01, 0x01, 0xff, 0x01, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x7c, 0xfe, 0x00, 0xc0, 0xc0, 0xfe, 0x7c, 0x00,
	0x7c, 0xfe, 0x00, 0xc0, 0xc0, 0xfe, 0x7c, 0x00,
	0xfe, 0xfe, 0x00, 0xf0, 0xc0, 0xfe, 0xfe, 0x00,
	0xfe, 0xfe, 0x00, 0xf0, 0xc0, 0xfe, 0xfe, 0x00,
};

char chr_end[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
