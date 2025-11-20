#include <stddef.h>
#include "big_shift.h"

void left_shift(const unsigned char *big_int, unsigned char *buf, size_t size, size_t Nbits) {
	size_t Nbytes = Nbits / 8;
	size_t Nbits_mod = Nbits % 8;

	for (size_t i = Nbytes; i < size; ++i) {
		buf[i - Nbytes] = (big_int[i] << Nbits_mod) | (big_int[i  + 1] >> (8 - Nbits_mod));
	}
	buf[size - 1 - Nbytes] = big_int[size - 1] << Nbits_mod;
	for (int i = size - Nbytes; i < size; ++i) {
		buf[i] = 0;
	}
}
