#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//generate random number, if < packet loss, don't send packet
//source port 54809 destination port 54810
struct sockaddr_in SourceAddr, DestinationAddr;

int main(int args, char** argv)
{
	char buff[2048]; //Buffer to hold the packets in
	int n, fdS, fdD;
	int DestAddrLen; //The destination address length
	int SourceAddrLen; //The source address length
	int lossRate = atoi(argv[5]);  //Determine the loss rate
	int random;

	int sourcePort = atoi(argv[2]); //Determine the source port
	int destPort = atoi(argv[4]); //Determine the destination port
	
	printf("Source IP: %s, Source Port: %d, Destination IP: %s, Destination Port: %d, Loss Rate: %d\n", argv[1], sourcePort, argv[3], destPort, lossRate);
	//Construct the source address
	SourceAddr.sin_family = AF_INET;
	SourceAddr.sin_port = htons(sourcePort);
	SourceAddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	//Construct the destination address
	DestinationAddr.sin_family = AF_INET;
	DestinationAddr.sin_port = htons(destPort);
	DestinationAddr.sin_addr.s_addr = inet_addr(argv[3]);

	//Get the size of both the addresses
	DestAddrLen = sizeof(DestAddrLen);
	SourceAddrLen = sizeof(SourceAddr);
	
	//Open the sockets for the source and destination, bind the source address
	fdS = socket(AF_INET, SOCK_DGRAM, 0);
	fdD = socket(AF_INET, SOCK_DGRAM, 0);
	bind(fdS, &SourceAddr, SourceAddrLen);

	for(;;)
	{
		//receive and store a packet from the source
		n = recvfrom(fdS, buff, 2048, 0, &SourceAddr, &SourceAddrLen);
		
		printf("%d ", n);
		//generate a random value 0-100
		srand(time(NULL));
		random = rand() % 101;
		//printf("%d ", random);
		//check if the random value is less than the loss rate, if it is, don't send the packet, if it is not, send the packet
		if(random <= lossRate);
			continue;
		else
		{
			//send the packet to the destination
			sendto(fdD, buff, n, 0, &DestinationAddr, DestAddrLen);
		}
	}
	return 0;
}
