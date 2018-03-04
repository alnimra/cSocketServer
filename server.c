#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int				   fd;
	int				   sock;
	int				   ret;
	struct sockaddr_in addr;
	int				   addr_len;
	addr_len = sizeof(addr);
	char  buf[1024];
	char *msg;
	msg = "pong pong\n";
	fd = 0;
	fork();
	if (argc != 2)
	{
		printf("USAGE ./server [VALID PORT]\n");
		exit(1);
	}
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		printf("Creation of socket failed\n");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(atoi(argv[1]));
	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		printf("Binding of socket to %d port failed\n", atoi(argv[1]));
		exit(1);
	}
	if (listen(fd, 10) < 0)
	{
		printf("Unable to listen\n");
		exit(1);
	}
	printf("Listening on port %d\n", atoi(argv[1]));
	if ((sock = accept(fd, (struct sockaddr *)&addr, (socklen_t *)&addr_len)) <
		0)
		printf("Could not accept the connection\n");
	while (1)
	{

		ret = read(sock, buf, 1024);
		if (strcmp(buf, "ping") == 0)
			send(sock, msg, strlen(msg), 0);
		printf("Recieved: %s\n", buf);
	}
	return (0);
}
