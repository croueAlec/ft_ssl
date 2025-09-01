#include <stdio.h>

#define INIT_VECTOR_A 0x01234567
#define INIT_VECTOR_B 0x89abcdef
#define INIT_VECTOR_C 0xfedcba98
#define INIT_VECTOR_D 0x76543210

/* S specifies the per-round shift amounts */
#define S { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,\
			5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,\
			4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,\
			6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 }

typedef struct initialization_vectors
{
	u_int32_t	a;
	u_int32_t	b;
	u_int32_t	c;
	u_int32_t	d;
}			init_vectors;

#define F(b, c, d) (((b) & (c)) | ((~b) & (d)))
#define G(b, c, d) (((b) & (d)) | ((c) & (~d)))
#define H(b, c, d) ((b) ^ (c) ^ (d))
#define I(b, c, d) ((c) ^ ((b) | (~d)))
