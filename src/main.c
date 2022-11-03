#include "psutil.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	int retval;
	char buffer[1024];
	char err_buf[512];

	retval = execute_command_get_output("ls", buffer , 1024, 
						  5,"-l","-a","--color=auto","-h","/var");
	if (retval != 0){
		printf("not successful run!\n");
	} else{
		printf("successful run.\n");
		printf("output:\n%s\n", buffer);
	}
	retval = execute_command_simple("ls", 5,"-l","-a","--color=auto","-h","/var");
	if (retval != 0){
		printf("not successful run!\n");
	} else{
		printf("successful run.\n");
	}
	retval = execute_command_get_error ("laas", buffer , 1024, 
						  5,"-l","-a","--color=auto","-h","/var");
	if (retval != 0){
		printf("not successful run!\n");
		printf("command error: %s\n", buffer);
	} else{
		printf("successful run.\n");
	}
	retval = execute_command("laas",err_buf, 512, buffer , 1024, 
						  5,"-l","-a","--color=auto","-h","/var");
	if (retval != 0){
		printf("not successful run!\n");
		printf("command error: %s\n", err_buf);
	} else{
		printf("successful run.\n");
		printf("output:\n%s\n", buffer);
	}
	return 0;
}
