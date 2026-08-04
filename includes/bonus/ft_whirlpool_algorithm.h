#ifndef FT_WHIRLPOOL_ALGORITHM_H
#define FT_WHIRLPOOL_ALGORITHM_H

#include <stdint.h>
#include "ft_whirlpool.h"

#define WHIRLPOOL_POLYNOMIAL_MODULO 0x1D

typedef struct block_512_bits_whirlpool t_block_whirlpool;

/* 		Constants			 */

extern const uint8_t S_matrix[16][16];
extern const uint8_t C_matrix[MATRIX_SIZE][MATRIX_SIZE];

/* 		Algorithm Utils		 */

void	bit_operation(whirlpool_matrix new_values, const whirlpool_matrix cstate, const whirlpool_matrix message_block, const whirlpool_matrix init_values);
uint8_t galois_field_add(uint8_t a, uint8_t b);
uint8_t galois_field_mult(uint8_t a, uint8_t b);
void	populate_round_constant(whirlpool_matrix RoundConstant, size_t round);
void	whirlpool_update(t_block_whirlpool *block);

#endif
