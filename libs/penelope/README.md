# Penelope; the debugging library
made by acroue

The current log_level can be changed using the `P_LOG_LEVEL` define in [penelope.h](./penelope.h).

The main usage of this lib is the `print_level` function.\
It implements a variation of the standard log levels :
1. NONE - [**P_LOG_NONE**]	>	Will not print anything. It has no associated function.
1. Fatal - [**P_LOG_FATAL**]	>	Prints only **Fatal Errors** that cause the program to stop when they happen.
1. Error - [**P_LOG_ERROR**]	>	Prints **Fatal and non-Fatal Errors** to STDERR.
1. DEFAULT - [**P_LOG_DEFAULT**]	>	The default printing level. Useful for regular program outputs. Also prints Errors and Fatal Errors.
1. Informational - [**P_LOG_INFO**]	> Prints **basic information** such as certain **function call checkpoints**.
1. Debug - [**P_LOG_DEBUG**] >	Prints debugging info such as **important variables**.
1. Trace - [**P_LOG_TRACE**]	>	Prints the program's **steps and variables** in the most **verbose** way implemented. This is the **deepest** log_level.

By default these log levels (except [**P_LOG_FATAL**] and [**P_LOG_ERROR**]) will print to **STDOUT**, this can be changed using this define found in [penelope.h](./penelope.h):

```c
#ifndef PENELOPE_LOG_OUTPUT
# define PENELOPE_LOG_OUTPUT STDOUT_FILENO
#endif
```

The default error log output can be changed in [penelope.h](./penelope.h) as well with this define :

```c
#ifndef PENELOPE_ERROR_OUTPUT
# define PENELOPE_ERROR_OUTPUT STDERR_FILENO
#endif
```

These log levels are cumulative, which means level **DEFAULT** will print **ERROR**s as well as **FATAL**.

You can use either the mother function `p_print_level()` or each of the sister function.
```c
void	p_print_level(t_penelope_log_level log_level, char const *format, ...);
```

#### Fatal
```c
void	p_print_fatal(char const *format, ...); // Will always print as FATAL
```

#### Error
```c
void	p_print_error(char const *format, ...); // Will always print as ERROR
```

#### Default
```c
void	p_print_default(char const *format, ...); // Will always print as DEFAULT
```

#### Informational
```c
void	p_print_info(char const *format, ...); // Will always print as INFO
```

#### Debug
```c
void	p_print_debug(char const *format, ...); // Will always print as DEBUG
```

#### Trace
```c
void	p_print_trace(char const *format, ...); // Will always print as TRACE
```

There are also two more log levels that are independent from the log_level system above :
1. **P_LOG_USR_OUTPUT1** < Prints on **STDOUT by default**
2. **P_LOG_USR_OUTPUT2** < Prints on **STDERR by default**

These two log_levels don't have a specific use. By default, they will print but you can disable them using their respective defines.\
Just like with the default log_level system, you can change the output of each of these logs independently in the `penelope.h` header file :

```c
#ifndef PENELOPE_LOG_USR_OUTPUT1
# define PENELOPE_LOG_USR_OUTPUT1 STDOUT_FILENO
#endif

#ifndef ENABLE_USR_OUTPUT1
# define ENABLE_USR_OUTPUT1 true
#endif
```

```c
#ifndef PENELOPE_LOG_USR_OUTPUT2
# define PENELOPE_LOG_USR_OUTPUT2 STDERR_FILENO
#endif

#ifndef ENABLE_USR_OUTPUT2
# define ENABLE_USR_OUTPUT2 true
#endif
```

You can also use the `p_print_level()` mother function or each of the two children function with the USR_OUTPUTs :

```c
void	p_print_level(t_penelope_log_level log_level, char const *format, ...);
```

#### USR_OUTPUT1
```c
void	p_print_usr_output1(char const *format, ...);
```

#### USR_OUTPUT2
```c
void	p_print_usr_output2(char const *format, ...);
```


## Various printing functions

Penelope also offers various printing functions.


#### Bits printing
Prints the bits of a uint8_t value.
```c
void	p_print_bits_uint8(t_penelope_log_level log_level, uint8_t byte, char const *description, bool print_value);
```

Prints the bits of a uint32_t value.
```c
void	p_print_bits_uint32(t_penelope_log_level log_level, uint32_t value, bool print_value, char const *description, bool space_each_byte);
```

#### Level_verification
Returns true or false depending on the passed log_level. Useful for when you want to use a specific printing function while retaining the log_level system.
```c
bool	level_verification(t_penelope_log_level log_level);
```

Can be used like so.
```c
if (!level_verification(log_level))
	return ;
```
