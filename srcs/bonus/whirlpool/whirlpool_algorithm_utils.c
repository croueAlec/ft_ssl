#include "ft_ssl.h"
#include "bonus/ft_whirlpool.h"
#include "bonus/ft_whirlpool_algorithm.h"

void bit_operation(whirlpool_matrix new_values, const whirlpool_matrix cstate, const whirlpool_matrix message_block, const whirlpool_matrix init_values)
{
	for (size_t i = 0; i < MATRIX_SIZE; i++) {
		for (size_t j = 0; j < MATRIX_SIZE; j++) {
			new_values[i][j] = cstate[i][j] ^
							   message_block[i][j] ^
							   init_values[i][j];
		}
	}
}

uint8_t galois_field_add(uint8_t a, uint8_t b)
{
	return a ^ b;
}

uint8_t galois_field_mult(uint8_t a, uint8_t b)
{
	uint8_t result = 0;

	for (int i = 0; i < 8; i++) {
		if (b & 1) {
			result ^= a;
		}

		uint8_t modulo = a & 0b10000000;	 // this is an overflow check using 0d128 to keep a polynomial of degree <= 7
		a <<= 1;
		if (modulo) {
			a ^= WHIRLPOOL_POLYNOMIAL_MODULO;
		}

		b >>= 1;
	}

	return result;
}

void populate_round_constant(whirlpool_matrix RoundConstant, size_t round)
{
	memcpy(RoundConstant[0], &S_matrix[round / 2][MATRIX_SIZE * (round % 2)], MATRIX_SIZE);
}
