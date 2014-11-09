#include <sys/socket.h>
#include <netinet/in.h>
//#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h> //host database
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char* host;
	int sockfd;
	int len, result;
	struct sockaddr_in address;
	struct servent *servinfo;
	struct hostent *hostinfo;
	char buffer[128];

	//Set 'argv' or current user's host to the variant of 'host'
	if (argc == 1)
		host = "localhsot";
	else
		host = argv[1];

	//Call gethostbyname, do warning if nothing found
	hostinfo = gethostbyname(host);
	if (!hostinfo)
	{
		fprintf(stderr, "cannot get info for host: %s\n", host);
		exit(1);
	}

	//Check for if the daytime service existed on the host
	servinfo = getservbyname("daytime", "tcp");
	if (!servinfo)
	{
		fprintf(stderr, "no daytime service\n");
		exit(1);
	}

	//Create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//Generate address for connect
	address.sin_family = AF_INET;
	address.sin_port = servinfo->s_port;
	address.sin_addr = *(struct in_addr*)*hostinfo->h_addr_list;
	len = sizeof(address);

	//connect and fetch info
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if (result == -1)
	{
		perror("opps: getdate");
		exit(1);
	}
	result = read(sockfd, buffer, sizeof(buffer));
	buffer[result] = '\0';
	printf("read %d bytes: %s", result, buffer);
	close(sockfd);
	exit(0);
}
