#include "penelope.h"

/**
 * @brief Compares log_level with current P_LOG_LEVEL and if allowed, prints the format on fd with it's arguments.
 */
static void	penelope_vdprintf(int fd, char const *format, va_list args, t_penelope_log_level log_level)
{
	if (log_level <= P_LOG_LEVEL || log_level == P_LOG_USR_OUTPUT1 || log_level == P_LOG_USR_OUTPUT2)
		vdprintf(fd, format, args);
}

/**
 * @brief Handles the calls to vdprintf(), changing output file descriptor depending on log_level.
 */
void	penelope_print_level(t_penelope_log_level log_level, char const *format, va_list args)
{
	if (P_LOG_LEVEL == P_LOG_NONE)
		return ;

	switch (log_level)
	{
	case P_LOG_NONE:
		break;

	case P_LOG_USR_OUTPUT1:
		penelope_vdprintf(PENELOPE_LOG_USR_OUTPUT1, format, args, log_level);
		break;
	case P_LOG_USR_OUTPUT2:
		penelope_vdprintf(PENELOPE_LOG_USR_OUTPUT2, format, args, log_level);
		break;


	case P_LOG_FATAL:
	case P_LOG_ERROR:
		penelope_vdprintf(PENELOPE_ERROR_OUTPUT, format, args, log_level);
		break;


	case P_LOG_DEFAULT:
	case P_LOG_INFO:
	case P_LOG_DEBUG:
	case P_LOG_TRACE:
		penelope_vdprintf(PENELOPE_LOG_OUTPUT, format, args, log_level);
		break;


	default:
		dprintf(STDERR_FILENO, "Penelope: Invalid penelope_log_level %d\n", log_level);
		break;
	}
}

/**
 * @brief Prints the format with it's variadic arguments if log_level is inferior or equal to P_LOG_LEVEL.
 */
void	p_print_level(t_penelope_log_level log_level, char const *format, ...)
{
	va_list	args;
	va_start(args, format);

	penelope_print_level(log_level, format, args);

	va_end(args);
}

/**
 * @brief Returns True or False depending on the log_level argument when compared with P_LOG_LEVEL.
 */
bool	level_verification(t_penelope_log_level log_level)
{
	if (P_LOG_LEVEL == P_LOG_NONE || log_level == P_LOG_NONE)
		return (false);

	if (log_level == P_LOG_USR_OUTPUT1 || log_level == P_LOG_USR_OUTPUT2)
	{
		if (log_level == P_LOG_USR_OUTPUT1 && ENABLE_USR_OUTPUT1 == true)
			return (true);
		else if (log_level == P_LOG_USR_OUTPUT2 && ENABLE_USR_OUTPUT2 == true)
			return (true);
		else
			return (false);
	}

	if (log_level <= P_LOG_LEVEL)
		return (true);
	else
		return (false);
}
