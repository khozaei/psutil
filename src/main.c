#include "psutil.h"

#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int retval;
	char buffer[1024];

	retval = execute_command("ls", NULL , 0,
						  buffer, 1024, 
						  5,"-l","-a","--color=auto","-h","/var");
	if (retval != 0){
		printf("not successful run!\n");
	} else{
		printf("successful run.\n");
		printf("output:\n%s\n", buffer);
	}
	return 0;
}
