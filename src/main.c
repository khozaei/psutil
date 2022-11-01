#include "psutil.h"

#include <stdlib.h>

int
main(int argc, char *argv[])
{
	execute_command("ls",4,"-l","-a","--color=auto","-h",(char *)NULL);

	return 0;
}
