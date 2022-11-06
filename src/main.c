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
