#include "ft_ssl.h"

#include "bonus/ft_whirlpool.h"
#include "bonus/ft_whirlpool_algorithm.h"

/**
 * @brief See [Figure 2] and the Transformation Matrix (here implemented as C_Matrix).
 * This part is the most difficult to understand.
 * C_Matrix is used as a Galois Field GF(2^8).
 * It applies a Galois Field Addition (binary addition), on the result of the Galois Field Multiplication.
 * It represents polynomials using the bits of the matrix's values.
 */
static void mixRows(whirlpool_matrix modified_array)
{
	whirlpool_matrix tmp = {};

	memcpy(tmp, modified_array, 64);

	for (size_t i = 0; i < MATRIX_SIZE; i++) {
		for (size_t j = 0; j < MATRIX_SIZE; j++) {
			uint8_t sum = 0;
			for (size_t k = 0; k < MATRIX_SIZE; k++) {
				sum = galois_field_add(sum, galois_field_mult(tmp[i][k], C_matrix[k][j]));
			}
			modified_array[i][j] = sum;
		}
	}
}

/**
 * @brief This function implements a circular downwards shift of each column in the matrix.
 * Each column must be shifted by it's index. Column 0 is shifted by 0, column 1 by 1...
 * Columns are copied in an array and this array is then copied back with the required shift
 */
static void shiftColumns(whirlpool_matrix modified_array)
{
	uint8_t fake_column[MATRIX_SIZE];

	for (size_t col = 0; col < MATRIX_SIZE; col++) {
		for (size_t row = 0; row < MATRIX_SIZE; row++)
			fake_column[(row + col) % MATRIX_SIZE] = modified_array[row][col];

		for (size_t row = 0; row < MATRIX_SIZE; row++)
			modified_array[row][col] = fake_column[row];
	}
}

/**
 * @brief See [Figure 2] and [Table 2 - (a)].
 * This function substitutes Bytes using the S-Box (here implemented as a Matrix).
 * This Matrix contains a permutation of all possible 256 8-bit values.
 * Values are substitued using the values of the original array as coordinates.
 * The upper half of the byte is used for the row, and the lower half for the column.
 */
static void subBytes(whirlpool_matrix modified_array)
{
	uint8_t row = 0;
	uint8_t col = 0;

	for (size_t i = 0; i < 64; i++) {
		row = (modified_array[i / MATRIX_SIZE][i % MATRIX_SIZE] & 0xf0) >> 4;
		col = modified_array[i / MATRIX_SIZE][i % MATRIX_SIZE] & 0x0f;
		modified_array[i / MATRIX_SIZE][i % MATRIX_SIZE] = S_matrix[row][col];
	}
}

/**
 * @brief See [Figure 2]. This implements a binary addition
 */
static void addRoundKey(whirlpool_matrix modified_array, const whirlpool_matrix roundKey)
{
	for (size_t i = 0; i < MATRIX_SIZE; i++) {
		for (size_t j = 0; j < MATRIX_SIZE; j++) {
			modified_array[i][j] ^= roundKey[i][j];
		}
	}
}

/**
 * @brief This function implements both the Round # and Key Expansion of [Figure 2]
 *
 * @param modified_array is either CState or KState depending on context
 * @param added_array is either KState or the RoundConstant matrix depending on context
 */
static void w_round(whirlpool_matrix modified_array, const whirlpool_matrix added_array)
{
	subBytes(modified_array);
	shiftColumns(modified_array);
	mixRows(modified_array);
	addRoundKey(modified_array, added_array);
}

/**
 * @brief This function implements [Figure 2] with it's initial addRoundKey
 * followed by the 10 rounds, each containing the Key Expansion and Round #
 *
 * @param CState is the plaintext chunk represented as the Cypher Matrix (see [Figure 3])
 * CState will become CypherText. On the next iteration (chunk) it will in turn become KState
 * @param KState is the previous hashed state as the Cypher Matrix
 */
static void W(whirlpool_matrix CState, whirlpool_matrix KState)
{
	addRoundKey(CState, KState);

	for (size_t i = 0; i < 10; i++) {
		whirlpool_matrix RoundConstant = {0};
		populate_round_constant(RoundConstant, i);

		w_round(KState, RoundConstant);
		w_round(CState, KState);
	}
}

/**
 * @brief This function is based on [Figure 1] of the paper.
 * It initializes the various matrices that will either
 *  be changed by the algorithm or used in their initial states
 * for the final bit_operation.
 *
 *
 */
void whirlpool_update(t_block_whirlpool *block)
{
	whirlpool_matrix CState = {0};
	whirlpool_matrix intermediate_H = {0};
	whirlpool_matrix initial_block_chunk = {0};

	memcpy(initial_block_chunk, block->chunk, whirlpool_CHUNK_SIZE);
	ft_bzero(block->result, whirlpool_CHUNK_SIZE);

	memcpy(CState, block->chunk, whirlpool_CHUNK_SIZE);
	memcpy(intermediate_H, block->H, whirlpool_CHUNK_SIZE);
	W(CState, intermediate_H);

	bit_operation(block->result, CState, initial_block_chunk, block->H);
}
