#ifndef PENELOPE_H
# define PENELOPE_H

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "penelope_tools.h"

#ifndef PENELOPE_ERROR_OUTPUT
// Default error output for the penelope debugging library
# define PENELOPE_ERROR_OUTPUT STDERR_FILENO
#endif

#ifndef PENELOPE_LOG_OUTPUT
// Default log output for the penelope debugging library
# define PENELOPE_LOG_OUTPUT STDOUT_FILENO
#endif

#ifndef PENELOPE_LOG_USR_OUTPUT1
// Default log output for USR_OUTPUT1 in the penelope debugging library
# define PENELOPE_LOG_USR_OUTPUT1 STDOUT_FILENO
#endif

#ifndef ENABLE_USR_OUTPUT1
// Toggling of USR_OUTPUT1
# define ENABLE_USR_OUTPUT1 true
#endif

#ifndef PENELOPE_LOG_USR_OUTPUT2
// Default log output for USR_OUTPUT1 in the penelope debugging library
# define PENELOPE_LOG_USR_OUTPUT2 STDERR_FILENO
#endif

#ifndef ENABLE_USR_OUTPUT2
// Toggling of USR_OUTPUT2
# define ENABLE_USR_OUTPUT2 true
#endif

typedef enum	e_penelope_log_level
{
	P_LOG_NONE = 0,	// < Will not print anything

	P_LOG_FATAL = 1,
	P_LOG_ERROR = 2,
	P_LOG_DEFAULT = 3,
	P_LOG_INFO = 4,
	P_LOG_DEBUG = 5,
	P_LOG_TRACE = 6,

	P_LOG_USR_OUTPUT1 = 9,
	P_LOG_USR_OUTPUT2 = 10
}	t_penelope_log_level;

extern t_penelope_log_level	P_LOG_LEVEL;

void	p_print_level(t_penelope_log_level log_level, char const *format, ...);

void	p_print_fatal(char const *format, ...);
void	p_print_error(char const *format, ...);
void	p_print_default(char const *format, ...);
void	p_print_info(char const *format, ...);
void	p_print_debug(char const *format, ...);
void	p_print_trace(char const *format, ...);
void	p_print_usr_output1(char const *format, ...);
void	p_print_usr_output2(char const *format, ...);

bool	level_verification(t_penelope_log_level log_level);

#endif
