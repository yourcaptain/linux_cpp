#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h> //host database
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char* host, **names, **addrs;
	struct hostent *hostinfo;

	//Set 'argv' or current user's host to the variant of 'host'
	if (argc == 1)
	{
		char myname[256];
		gethostname(myname, 255);
		host = myname;
	}
	else
	{
		host = argv[1];
	}

	//Call gethostbyname, do warning if nothing found
	hostinfo = gethostbyname(host);
	if (!hostinfo)
	{
		fprintf(stderr, "cannot get info for host: %s\n", host);
		exit(1);
	}

	//Print out it's host name and all aliases
	printf("results for host %s:\n", host);
	printf("Name: %s\n", hostinfo->h_name);
	printf("Aliases:");
	names = hostinfo->h_aliases;
	while(*names)
	{
		printf(" %s", *names);
		names++;
	}
	printf("\n");

	//if the host is not an IP host, then warning
	if (hostinfo -> h_addrtype != AF_INET)
	{
		fprintf(stderr, "not an IP host!\n");
		exit(1);
	}

	//Print out it's IP address
	addrs = hostinfo->h_addr_list;
	while(*addrs)
	{
		printf(" %s", inet_ntoa(* (struct in_addr*)*addrs));
		addrs++;
	}
	printf("\n");
	exit(0);
}
