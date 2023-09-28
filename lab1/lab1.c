#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	char msg[] = "Port test!\n";
	int port = open("/dev/tnt1", O_RDWR);
	if (port <= 0)
	{
		printf("Port open fail!\n");
		return 1;
	}
	write(port, msg, sizeof(msg));
	close(port);
	return 0;
}
