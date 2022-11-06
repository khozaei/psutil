/*
 * Copyright (c) 2022, Amin Khozaei <amin.khozaei@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "psutil.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>


Process *
process_new (const char *command, uint32_t error_len, uint32_t output_len)
{
	Process *p;
	uint32_t len;

	len = strnlen(command, 1024) + 1;
	p = malloc (sizeof(Process));
	if (error_len > 0)
		p->error_message = malloc (error_len);
	else
		p->error_message = NULL;
	p->error_len = error_len;
	p->output_len = output_len;
	if (output_len > 0)
		p->output = malloc (output_len);
	else
		p->output = NULL;
	p->command = malloc (len);
	snprintf (p->command, len, "%s", command);

	return p;
}

void
process_destroy (Process *process)
{
	if (process){
		if (process->command) {
			free (process->command);
			process->command = NULL;
		}
		if (process->output) {
			free (process->output);
			process->output = NULL;
		}
		if (process->error_message) {
			free (process->error_message);
			process->error_message = NULL;
		}
		free (process);
		process = NULL;
	}
}

void
process_set_command (Process *process, const char *command)
{
	if (process) {
		if (strnlen(process->command, 1024) == strnlen(command, 1024)) {
			snprintf (process->command, strnlen(process->command,1024) + 1,
				"%s", command);
		} else {
			uint32_t len;

			len = strnlen(command, 1024) + 1;
			free (process->command);
			process->command = malloc (len);
			snprintf(process->command, len, "%s", command);
		}
	}
}

int
process_set_path (const unsigned int path_count, ...)
{
	va_list va_ptr;
	char *args[path_count];
	char *joined_value;
	uint32_t len;
	uint32_t index;
	int retval;

	len = path_count;
	va_start (va_ptr, path_count);
	for (uint32_t i = 0; i < path_count; i++) {
		args[i] = va_arg (va_ptr, char *);
		len += strnlen (args[i], 1024);
	}
	va_end(va_ptr);
	joined_value = malloc (len);
	index = 0;
	for (uint32_t i = 0; i < path_count; i++) {
		for (uint32_t j = 0; j < strnlen (args[i],1024); j++) {
			joined_value[index++] = args[i][j];
		}
		if (i < path_count - 1)
			joined_value[index++] = ':';
	}
	retval = setenv ("PATH", joined_value, 1);
	free (joined_value);
	return retval;
}

int
process_execute (Process *process, const unsigned int arg_count, ...)
{
	va_list va_ptr;
	pid_t pid;
	int status, retval;
	int pipe_fd[2];
	char *argument_array[arg_count + 2];
	char *error_buffer;

	if (process != NULL) {
		error_buffer = mmap(NULL, process->error_len, PROT_READ | PROT_WRITE,
							MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	} else{
		return -1;
	}
	retval = pipe(pipe_fd);
	if (retval < 0){
		fprintf(stderr, "Can't create pipe: %s", strerror(errno));
		return retval;
	}
	argument_array[0] = process->command;
	va_start(va_ptr, arg_count);
	for(uint32_t i = 1; i <= arg_count; i++){
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

		dup2 (pipe_fd[1], STDOUT_FILENO);
		close (pipe_fd[0]);
		close (pipe_fd[1]);
		retval = execvp(process->command, &argument_array[0]);
		if (error_buffer != NULL){
			snprintf (error_buffer, process->error_len, 
				"%s: %s", process->command, strerror(errno));
		}
		exit(retval);
	} else {
		close (pipe_fd[1]);
		if (process != NULL && process->output_len > 0){
			read (pipe_fd[0], process->output, process->output_len);
		}
		waitpid(pid, &status, 0);
		if (process != NULL && process->error_len > 0) {
			snprintf (process->error_message, process->error_len,"%s", error_buffer);
			munmap(error_buffer, process->error_len);
		}
	}
	return status;
}
