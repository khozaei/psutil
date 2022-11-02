#include "psutil.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

void
set_process_env_path(const unsigned int path_count, ...)
{

}

int
execute_command(const char *command, const unsigned int arg_count, ...)
{
	va_list va_ptr;
	pid_t pid;
	int status;
	char *argument_array[arg_count + 2];

	argument_array[0] = (char *)command;
	va_start(va_ptr, arg_count);
	for(int i = 1; i <= arg_count; i++){
		argument_array[i] = va_arg(va_ptr, char *);
	}
	va_end(va_ptr);
	argument_array[arg_count + 1] = (char *)NULL;
	for(int i = 0; i <= arg_count + 1; i++){
		printf(">%s\t",argument_array[i]);		
	}
	printf("\n");
	pid = fork();
	if (pid < 0) {
		fprintf(stderr,"Can't fork: %s\n", strerror(errno));
		return 1;
	}
	else if (pid == 0) {
		int retval;

		retval = execvp(command, &argument_array[0]);
		fprintf(stderr,"Can't run %s: %s\n",command , strerror(errno));
		exit(retval);
	} else {
		waitpid(pid, &status, 0);
	}
	return status;
}

const char *
get_error_message(void)
{
	return "\0";
}
