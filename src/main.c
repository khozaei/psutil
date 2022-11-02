#include "psutil.h"

#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int retval;
	char buffer[1024];
	char err_buf[512];

	retval = execute_command("lsyyy", err_buf , 512,
						  buffer, 1024, 
						  5,"-l","-a","--color=auto","-h","/var");
	if (retval != 0){
		printf("not successful run!\n");
		printf("parent: command error: %s\n", err_buf);
	} else{
		printf("successful run.\n");
		printf("output:\n%s\n", buffer);
	}
	return 0;
}
