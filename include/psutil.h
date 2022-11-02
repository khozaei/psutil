#include <stdint.h>

void pre_execute_set_path (const unsigned int path_count, ...);

int _execute_command(const char *command, 
					char *out_error_msg, const uint16_t error_size,
					char *out_cmd_output, const uint16_t cmd_output_size,
					const unsigned int arg_count, ...);

#define execute_command_simple(CMD, ARGC, ...) \
	_execute_command (CMD, NULL, 0, NULL, 0, \
					  ARGC, __VA_ARGS__);

#define execute_command_get_error(CMD, \
		OUT_ERR, ERR_SIZE, ARGC, ...) \
		_execute_command(CMD, OUT_ERR, ERR_SIZE, \
				NULL, 0, ARGC, __VA_ARGS__);

#define execute_command_get_output(CMD, \
		OUT_OUTPUT, OUTPUT_SIZE, ARGC, ...) \
		_execute_command(CMD, NULL, 0, \
				OUT_OUTPUT, OUTPUT_SIZE, \
				ARGC, __VA_ARGS__);

#define execute_command(CMD, OUT_ERR, ERR_SIZE, \
		OUT_OUTPUT, OUTPUT_SIZE, ARGC, ...) \
		_execute_command(CMD, OUT_ERR, ERR_SIZE, \
				OUT_OUTPUT, OUTPUT_SIZE, ARGC, __VA_ARGS__);
