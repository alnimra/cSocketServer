/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 20:07:49 by mray              #+#    #+#             */
/*   Updated: 2018/03/03 20:07:51 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

void	create_and_bind_to_host_ip(int *sock, struct sockaddr_in *serv_addr,
								char *host_ip, int port)
{
	if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Creation of socket failed\n");
		exit(1);
	}
	(*serv_addr).sin_family = AF_INET;
	(*serv_addr).sin_port = htons(port);
	if (inet_pton(AF_INET, host_ip, &((*serv_addr).sin_addr)) <= 0)
	{
		printf("Ip Address is not valid\n");
		exit(1);
	}
}

int		main(int argc, char **argv)
{
	struct sockaddr_in	serv_addr;
	int					sock;
	int					ret;
	char				*msg;
	char				buf[1024];

	msg = argv[3];
	sock = 0;
	if (argc != 4)
	{
		printf("USAGE ./server [HOST IP] [VALID PORT] [MSG]\n");
		exit(1);
	}
	create_and_bind_to_host_ip(&sock, &serv_addr, argv[2], atoi(argv[1]));
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Conection to host failed");
		return (0);
	}
	send(sock, msg, strlen(msg), 0);
	ret = read(sock, buf, 1024);
	printf("%s\n", buf);
	return (0);
}
