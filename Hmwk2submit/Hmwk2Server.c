#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in ServAddr, ClientAddr;

/**
 * I do not know if this is working, the computers in Coover 2048 would compile my code, but then not print the commented print statements.
 * I have understand the theory of this and believe this code should work, but every change I made would compile with no errors or warnings,
 * then not execute.
 */
int main(int args, char** argv)
{
	//printf("1");
	char buff[1600];
	int n, fd, r;
	socklen_t ClientAddrLen;

	//printf("2");
	//Construct the server address
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(33333);
	ServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(fd, (struct sockaddr*)&ServAddr, sizeof(ServAddr));
	
	//printf("3");
	for(;;)
	{
		n = recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr*)&ClientAddr, &ClientAddrLen);
		//printf("%d ", n);
		r++;
		if(r == 10)
		{
			r = 0;
			char* message = " packets received";
			char ack[256];
			sprintf(ack, "%d", r);
			//printf("%s\n", message);
			strcat(ack, message);
			sendto(fd, ack, 256, 0, (struct sockaddr*)&ClientAddr, ClientAddrLen);
		}
	}
	return 0;
}
