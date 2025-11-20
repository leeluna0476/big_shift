#include "big_shift.h"

static size_t atoi_hex(const char *src, unsigned char **dst, size_t slen) {
	size_t bits = slen * 4;
	size_t bytes = bits % 8 ? bits / 8 + 1 : bits / 8;
	*dst = malloc(bytes);
	if (!(*dst)) {
		return 0;
	}

	size_t si = slen;
	size_t bi = bytes;
	while (bi > 0) {
		unsigned char u = 0;
		size_t end = si >= 2 ? si - 2 : 0;
		while (si > end) {
			unsigned char shifts = ((slen & 1) && (si == 1) ? 1 - (si - end) : 2 - (si - end)) * 4;
			u |= (src[si - 1] - '0') << shifts;
			--si;
		}
		(*dst)[bi - 1] = u;
		--bi;
	}

	return bytes;
}

static size_t atoi_bin(const char *src, unsigned char **dst, size_t slen) {
	size_t bytes = slen % 8 ? slen / 8 + 1 : slen / 8;
	*dst = malloc(bytes);
	if (!(*dst)) {
		return 0;
	}

	size_t si = slen;
	size_t bi = bytes;
	while (bi > 0) {
		unsigned char u = 0;
		size_t end = si >= 8 ? si - 8 : 0;
		size_t bitlen = si - end;
		while (si > end) {
			unsigned char shifts = bitlen - (si - end);
			u |= (src[si - 1] - '0') << shifts;
			--si;
		}
		(*dst)[bi - 1] = u;
		--bi;
	}

	return bytes;
}

size_t atoi_bigint(const char *src, unsigned char **dst, base_t base) {
	static size_t (*fp[3])(const char *, unsigned char **, size_t) = { atoi_hex, atoi_hex, atoi_bin };

	size_t slen = strlen(src);
	if (!slen) {
		return 0;
	}

	return fp[base](src, dst, slen);
}
