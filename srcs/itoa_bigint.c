#include "big_shift.h"

static char hextoc(unsigned char u) {
	return u < 10 ? u + '0' : u - 10 + 'A';
}

static char *hextoa_bigint(const unsigned char *big_int, size_t size) {
	if (!size) {
		fprintf(stderr, "Please give a valid size (size > 0)\n");
		return NULL;
	}

	size_t slen = size << 1;
	char *buf = malloc(slen + 1);
	if (!buf) {
		perror("malloc");
		return NULL;
	}

	char *s = buf;
	if (!(big_int[0] & 0xf0)) {
		s[0] = hextoc(big_int[0] & 0x0f);
		++s;
		++big_int;
		--size;
		--slen;
	}
	for (size_t i = 0; i < size; ++i) {
		size_t si = i << 1;
		s[si] = hextoc(big_int[i] >> 4);
		s[si + 1] = hextoc(big_int[i] & 0x0f);
	}
	buf[slen] = '\0';

	return buf;
}

char *itoa_bigint(const unsigned char *big_int, size_t size, base_t base) {
	return hextoa_bigint(big_int, size);
}
