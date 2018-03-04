#include <sys/socket.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	struct sockaddr_in serv_addr;
	int				   sock;
	int				   ret;
	char *			   msg;

	msg = argv[3];
	char buf[1024];

	sock = 0;
	if (argc != 3)
	{
		printf("USAGE ./server [HOST IP] [VALID PORT] [MSG]\n");
		exit(1);
	}
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Creation of socket failed\n");
		return (0);
	}
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
	{
		printf("Ip Address is not valid\n");
		return (0);
	}
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Conection to host failed");
		return (0);
	}
	send(sock, msg, strlen(msg), 0);
	ret = read(sock, buf, 1024);
	printf("%s\n", buf);
	return 0;
}
