#include "penelope.h"

/**
 * @brief Prints the individual bits of an uint8_t value at the LOG_LEVEL log_level. Allows printing of the original value as hexadecimal.
 */
void	p_print_bits_uint8(t_penelope_log_level log_level, uint8_t byte, char const *description, bool print_value)
{
	if (print_value == true)
		p_print_level(log_level, "%s0x%08x", description, byte);
	p_print_level(log_level, "0b%d%d%d%d%d%d%d%d\n",
		(byte >> 7) & 1, (byte >> 6) & 1, (byte >> 5) & 1, (byte >> 4) & 1,
		(byte >> 3) & 1, (byte >> 2) & 1, (byte >> 1) & 1, (byte & 1));
}

/**
 * @brief Prints the individual bits of an uint32_t value at the LOG_LEVEL log_level. Allows spacing of each byte using a space character. Allows the printing of the original value as hexadecimal alongside description.
 */
void	p_print_bits_uint32(t_penelope_log_level log_level, uint32_t value, bool print_value, char const *description, bool space_each_byte)
{
	p_print_level(log_level, "%s0x%08x = 0b", description, value);
	for (int i = 31; i >= 0; i--)
	{
		p_print_level(log_level, "%d", (value >> i) & 0b1);
		if (i % 8 == 0 && space_each_byte == true)
			p_print_level(log_level, " ");
	}
	p_print_level(log_level, "\n");
}
