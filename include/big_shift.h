#ifndef BIG_SHIFT_H
# define BIG_SHIFT_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef enum {
	DEC = 0,
	HEX,
	BIN
} base_t;

typedef struct {
	unsigned char *p;
	size_t size;
} big_int;

void left_shift(const unsigned char *big_int, unsigned char *buf, size_t size, size_t Nbits);

// returns bytes of the converted data pointed by *dst
size_t assign(const char *src, unsigned char **dst, base_t base);
char *itoa_bigint(const unsigned char *big_int, size_t size, base_t base);

#endif
