#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
        char msg[100];
        int port = open("/dev/tnt0", O_RDWR);
        if (port <= 0)
        {
                printf("Port open fail!\n");
                return 1;
        }
        read(port, msg, sizeof(msg));
	printf("Str from port:\n%s", msg);
        close(port);
        return 0;
}
