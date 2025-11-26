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

#define P_DEFINE_LOG_NONE			0
#define P_DEFINE_LOG_FATAL			1
#define P_DEFINE_LOG_ERROR			2
#define P_DEFINE_LOG_DEFAULT		3
#define P_DEFINE_LOG_INFO			4
#define P_DEFINE_LOG_DEBUG			5
#define P_DEFINE_LOG_TRACE			6

#define P_DEFINE_LOG_USR_OUTPUT1	9
#define P_DEFINE_LOG_USR_OUTPUT2	10

typedef enum	e_penelope_log_level
{
	P_LOG_NONE = 0,	// < Will not print anything

	P_LOG_FATAL = P_DEFINE_LOG_FATAL,
	P_LOG_ERROR = P_DEFINE_LOG_ERROR,
	P_LOG_DEFAULT = P_DEFINE_LOG_DEFAULT,
	P_LOG_INFO = P_DEFINE_LOG_INFO,
	P_LOG_DEBUG = P_DEFINE_LOG_DEBUG,
	P_LOG_TRACE = P_DEFINE_LOG_TRACE,

	P_LOG_USR_OUTPUT1 = P_DEFINE_LOG_USR_OUTPUT1,
	P_LOG_USR_OUTPUT2 = P_DEFINE_LOG_USR_OUTPUT2
}	t_penelope_log_level;

extern t_penelope_log_level	P_LOG_LEVEL;

void	p_print_level(t_penelope_log_level log_level, char const *format, ...);
void	penelope_print_level(t_penelope_log_level log_level, char const *format, va_list args);

static inline void p_log_impl(t_penelope_log_level level, const char *format, ...) {
	va_list args;
	va_start(args, format);
	penelope_print_level(level, format, args);
	va_end(args);
}

#if (LOG_LEVEL < P_DEFINE_LOG_FATAL) == false
	#define p_print_fatal(format, ...) do { (void)(format); (void)(0, ##__VA_ARGS__); } while (0) /* NO-OP */
#else
	/**
	 * @brief Prints Fatal errors that cause the program to stop when they happen. Prints to PENELOPE_ERROR_OUTPUT.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_fatal(format, ...) \
		do {\
			p_log_impl(P_LOG_FATAL, format, ##__VA_ARGS__); \
		} while (0)
#endif



#if (LOG_LEVEL < P_DEFINE_LOG_ERROR) == false
	#define p_print_error(format, ...) do { (void)(format); (void)(0, ##__VA_ARGS__); } while (0) /* NO-OP */
#else
	/**
	 * @brief Prints non-fatal Errors to PENELOPE_ERROR_OUTPUT.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_error(format, ...) \
		do {\
			p_log_impl(P_LOG_ERROR, format, ##__VA_ARGS__); \
		} while (0)
#endif



#if (LOG_LEVEL < P_DEFINE_LOG_DEFAULT) == false
	#define p_print_default(format, ...) do { (void)(format); (void)(0, ##__VA_ARGS__); } while (0) /* NO-OP */
#else
	/**
	 * @brief The Default printing level. Useful for regular program outputs.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_default(format, ...) \
		do {\
			p_log_impl(P_LOG_DEFAULT, format, ##__VA_ARGS__); \
		} while (0)
#endif

#if (LOG_LEVEL < P_DEFINE_LOG_INFO) == false
	#define p_print_info(format, ...) do { (void)(format); (void)(0, ##__VA_ARGS__); } while (0) /* NO-OP */
#else
	/**
	 * @brief Prints an Informational message such as function call checkpoints.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_info(format, ...) \
		do {\
			p_log_impl(P_LOG_INFO, format, ##__VA_ARGS__); \
		} while (0)
#endif

#if (LOG_LEVEL < P_DEFINE_LOG_DEBUG) == false
	#define p_print_debug(format, ...) do { (void)(format); (void)(0, ##__VA_ARGS__); } while (0) /* NO-OP */
	// #define p_print_debug(format, ...) do { (void)(format); (void)(0, ##__VA_ARGS__); printf("Disabled debug"); } while (0)
#else
	/**
	 * @brief Prints Debugging info such as important variables.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_debug(format, ...) \
		do {\
			p_log_impl(P_LOG_DEBUG, format, ##__VA_ARGS__); \
			} while (0)
#endif



#if (LOG_LEVEL < P_DEFINE_LOG_TRACE) == false
	#define p_print_trace(format, ...) do { (void)(format); (void)(0, ##__VA_ARGS__); } while (0) /* NO-OP */
#else
	/**
	 * @brief A more verbose version of DEBUG, intended to be used to see more in more detail the flow of the program. This is the deepest log_level.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_trace(format, ...) \
		do {\
			p_log_impl(P_LOG_TRACE, format, ##__VA_ARGS__); \
		} while (0)
#endif



#if (P_LOG_USR_OUTPUT1 == false)
	#define p_print_usr_output1(format, ...) do { (void)(format); (void)(0, ##__VA_ARGS__); } while (0) /* NO-OP */
#else
	/**
	 * @brief Prints a message on PENELOPE_LOG_USR_OUTPUT1 file descriptor.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_usr_output1(format, ...) \
		do {\
			p_log_impl(P_LOG_USR_OUTPUT1, format, ##__VA_ARGS__); \
		} while (0)
#endif



#if (P_LOG_USR_OUTPUT2 == false)
	#define p_print_usr_output2(format, ...) do { (void)(format); (void)(0, ##__VA_ARGS__); } while (0) /* NO-OP */
#else
	/**
	 * @brief Prints a message on PENELOPE_LOG_USR_OUTPUT2 file descriptor.
	 * @param format const char* format
	 * @param ... Variadic Arguments (optional)
	 * @return void
	 */
	#define p_print_usr_output2(format, ...) \
		do {\
			p_log_impl(P_LOG_USR_OUTPUT2, format, ##__VA_ARGS__); \
		} while (0)
#endif

bool	level_verification(t_penelope_log_level log_level);

#endif
