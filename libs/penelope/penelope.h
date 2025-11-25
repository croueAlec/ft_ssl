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
void	penelope_print_level(t_penelope_log_level log_level, char const *format, va_list args);

#if LOG_LEVEL < P_LOG_FATAL
	#define p_print_fatal(format, ...) ;	/*  NO-OP  */
#else
	/**
	 * @brief Prints Fatal errors that cause the program to stop when they happen. Prints to PENELOPE_ERROR_OUTPUT.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_fatal(format, ...) \
		do {\
			if (__VA_ARGS__) { \
				va_list args; \
				va_start(args, format); \
				penelope_print_level(P_LOG_FATAL, format, args); \
				va_end(args); \
			} else { \
				penelope_print_level(P_LOG_FATAL, format, NULL); \
			} \
		} while (0);
#endif



#if LOG_LEVEL < P_LOG_ERROR
	#define p_print_error(format, ...) ;	/*  NO-OP  */
#else
	/**
	 * @brief Prints non-fatal Errors to PENELOPE_ERROR_OUTPUT.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_error(format, ...) \
		do {\
			if (__VA_ARGS__) { \
				va_list args; \
				va_start(args, format); \
				penelope_print_level(P_LOG_ERROR, format, args); \
				va_end(args); \
			} else { \
				penelope_print_level(P_LOG_ERROR, format, NULL); \
			} \
		} while (0);
#endif



#if LOG_LEVEL < P_LOG_DEFAULT
	#define p_print_default(format, ...) ;	/*  NO-OP  */
#else
	/**
	 * @brief The Default printing level. Useful for regular program outputs.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_default(format, ...) \
		do {\
			if (__VA_ARGS__) { \
				va_list args; \
				va_start(args, format); \
				penelope_print_level(P_LOG_DEFAULT, format, args); \
				va_end(args); \
			} else { \
				penelope_print_level(P_LOG_DEFAULT, format, NULL); \
			} \
		} while (0);
#endif



#if LOG_LEVEL < P_LOG_INFO
	#define p_print_info(format, ...) ;	/*  NO-OP  */
#else
	/**
	 * @brief Prints an Informational message such as function call checkpoints.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_info(format, ...) \
		do {\
			if (__VA_ARGS__) { \
				va_list args; \
				va_start(args, format); \
				penelope_print_level(P_LOG_INFO, format, args); \
				va_end(args); \
			} else { \
				penelope_print_level(P_LOG_INFO, format, NULL); \
			} \
		} while (0);
#endif



#if LOG_LEVEL < P_LOG_DEBUG
	#define p_print_debug(format, ...) ;	/*  NO-OP  */
#else
	/**
	 * @brief Prints Debugging info such as important variables.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_debug(format, ...) \
		do {\
			if (__VA_ARGS__) { \
				va_list args; \
				va_start(args, format); \
				penelope_print_level(P_LOG_DEBUG, format, args); \
				va_end(args); \
			} else { \
				penelope_print_level(P_LOG_DEBUG, format, NULL); \
			} \
		} while (0);
#endif



#if LOG_LEVEL < P_LOG_TRACE
	#define p_print_trace(format, ...) ;	/*  NO-OP  */
#else
	/**
	 * @brief A more verbose version of DEBUG, intended to be used to see more in more detail the flow of the program. This is the deepest log_level.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_trace(format, ...) \
		do {\
			if (__VA_ARGS__) { \
				va_list args; \
				va_start(args, format); \
				penelope_print_level(P_LOG_TRACE, format, args); \
				va_end(args); \
			} else { \
				penelope_print_level(P_LOG_TRACE, format, NULL); \
			} \
		} while (0);
#endif



#if P_LOG_USR_OUTPUT1 == true
	#define p_print_usr_output1(format, ...) ;	/*  NO-OP  */
#else
	/**
	 * @brief Prints a message on PENELOPE_LOG_USR_OUTPUT1 file descriptor.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_usr_output1(format, ...) \
		do {\
			if (__VA_ARGS__) { \
				va_list args; \
				va_start(args, format); \
				penelope_print_level(P_LOG_USR_OUTPUT1, format, args); \
				va_end(args); \
			} else { \
				penelope_print_level(P_LOG_USR_OUTPUT1, format, NULL); \
			} \
		} while (0);
#endif



#if P_LOG_USR_OUTPUT2 == true
	#define p_print_usr_output2(format, ...) ;	/*  NO-OP  */
#else
	/**
	 * @brief Prints a message on PENELOPE_LOG_USR_OUTPUT2 file descriptor.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_usr_output2(format, ...) \
		do {\
			if (__VA_ARGS__) { \
				va_list args; \
				va_start(args, format); \
				penelope_print_level(P_LOG_USR_OUTPUT2, format, args); \
				va_end(args); \
			} else { \
				penelope_print_level(P_LOG_USR_OUTPUT2, format, NULL); \
			} \
		} while (0);
#endif

bool	level_verification(t_penelope_log_level log_level);

#endif
