#include <unistd.h>

main()
{
	if(execlp("./arg","./arg","abc","xyz","pqr",(char*)0)==-1)
		perror();
}
