#include "psutil.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>

void
pre_excecute_set_path (const unsigned int path_count, ...)
{

}

int
_execute_command(const char *command, char *out_error_msg, const uint16_t error_size,
				char *out_cmd_output, const uint16_t cmd_output_size,
				const unsigned int arg_count, ...)
{
	va_list va_ptr;
	pid_t pid;
	int status, retval;
	int pipe_fd[2];
	char *argument_array[arg_count + 2];
	char *error_buffer;

	if (error_size > 0 && out_error_msg != NULL) {
		error_buffer = mmap(NULL, error_size, PROT_READ | PROT_WRITE,
							MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	}
	retval = pipe(pipe_fd);
	if (retval < 0){
		fprintf(stderr, "Can't create pipe: %s", strerror(errno));
		return retval;
	}
	argument_array[0] = (char *)command;
	va_start(va_ptr, arg_count);
	for(int i = 1; i <= arg_count; i++){
		argument_array[i] = va_arg(va_ptr, char *);
	}
	va_end(va_ptr);
	argument_array[arg_count + 1] = (char *)NULL;
	pid = fork();
	if (pid < 0) {
		fprintf(stderr,"Can't fork: %s\n", strerror(errno));
		return 1;
	}
	else if (pid == 0) {
		int retval;
		int errcode;

		dup2 (pipe_fd[1], STDOUT_FILENO);
		close (pipe_fd[0]);
		close (pipe_fd[1]);
		retval = execvp(command, &argument_array[0]);
		if (error_buffer != NULL){
			snprintf (error_buffer, error_size, "%s: %s", command, strerror(errno));
		}
		exit(retval);
	} else {
		close (pipe_fd[1]);
		if (cmd_output_size > 0 && out_cmd_output != NULL){
			read (pipe_fd[0], out_cmd_output, cmd_output_size);
		}
		waitpid(pid, &status, 0);
		if (error_buffer != NULL) {
			snprintf (out_error_msg, error_size,"%s", error_buffer);
			munmap(error_buffer, error_size);
		}
	}
	return status;
}
