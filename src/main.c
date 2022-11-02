#include "psutil.h"

#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int retval;

	retval = execute_command("ls",5,"-l","-a","--color=auto","-h","/var");
	if (retval != 0){
		printf("not successful run!\n");
	} else{
		printf("successful run.\n");
	}
	return 0;
}
