#include <stdint.h>

void pre_execute_set_path (const unsigned int path_count, ...);

int execute_command(const char *command, char *out_error_msg, const uint16_t error_size,
					char *out_cmd_output, const uint16_t cmd_output_size,
					const unsigned int arg_count, ...);
