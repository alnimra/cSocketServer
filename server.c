/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:44:58 by mray              #+#    #+#             */
/*   Updated: 2018/03/03 19:45:01 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void	create_and_bind_socket(int *fd, struct sockaddr_in *addr, int port)
{
	if ((*fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		printf("Creation of socket failed\n");
		exit(1);
	}
	(*addr).sin_family = AF_INET;
	(*addr).sin_addr.s_addr = INADDR_ANY;
	(*addr).sin_port = htons(port);
	if (bind(*fd, (struct sockaddr *)&addr, sizeof(*addr)) < 0)
	{
		printf("Binding of socket to %d port failed\n", port);
		exit(1);
	}
}

void	listen_and_accept_connections(int *fd, struct sockaddr_in *addr,
									int *sock, int port)
{
	if (listen(*fd, 10) < 0)
	{
		printf("Unable to listen\n");
		exit(1);
	}
	printf("Listening on port %d\n", port);
	if ((*sock = accept(*fd, (struct sockaddr *)&(*addr),
						(socklen_t *)(sizeof(*addr)))) < 0)
		printf("Could not accept the connection\n");
}

int		main(int argc, char **argv)
{
	int					fd;
	int					sock;
	int					ret;
	struct sockaddr_in	addr;
	char				buf[1024];

	fd = 0;
	if (argc != 2)
	{
		printf("USAGE ./server [VALID PORT]\n");
		exit(1);
	}
	create_and_bind_socket(&fd, &addr, atoi(argv[1]));
	while (1)
	{
		listen_and_accept_connections(&fd, &addr, &sock, atoi(argv[1]));
		ret = read(sock, buf, 1024);
		if (strcmp(buf, "ping") == 0)
			send(sock, "pong pong", strlen("pong pong"), 0);
		printf("Recieved: %s\n", buf);
	}
	return (0);
}
