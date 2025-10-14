#ifndef PENELOPE_TOOLS_H
# define PENELOPE_TOOLS_H

#include "penelope.h"

typedef enum e_penelope_log_level	t_penelope_log_level;

void	p_print_bits_uint8(t_penelope_log_level log_level, uint8_t byte, char const *description, bool print_value);
void	p_print_bits_uint32(t_penelope_log_level log_level, uint32_t value, bool print_value, char const *description, bool space_each_byte);

#endif
