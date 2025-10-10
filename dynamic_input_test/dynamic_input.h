#ifndef DYNAMIC_INPUT_H
# define DYNAMIC_INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

#define BLOCK_SIZE 64

#define SEPARATOR 0b10000000

typedef struct	s_input
{
	int		fd;
	char	*str;
}				t_input;

char	*get_all_lines(int fd);

#endif
