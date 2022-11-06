/*
 * Copyright (c) 2022, Amin Khozaei <amin.khozaei@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "psutil.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	int retval;
	Process *process;

	process = process_new("ls",0,1024);
	if (!process)
		return -1;
	retval = process_set_path (1, "/bin");
	retval = process_execute (process, 5, "-l", "-a", "--color=auto", "-h", "/var");
	if (retval != 0){
		printf("not successful run!\n");
	} else{
		printf("successful run.\n");
		printf("output:\n%s\n", process->output);
	}
	process_destroy (process);
	return 0;
}
