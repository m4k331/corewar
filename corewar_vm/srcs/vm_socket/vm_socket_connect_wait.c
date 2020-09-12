/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_connect_wait.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:02:27 by limry             #+#    #+#             */
/*   Updated: 2020/09/08 18:44:06 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static int			socket_setkeepalive(int sockfd)
{
	int				yes;
	int				idle;
	int				interval;
	int				maxpkt;

	yes = KEEPALIVE_ON;
	idle = KEEPALIVE_IDLE;
	interval = KEEPALIVE_INTL;
	maxpkt = KEEPALIVE_MAXP;
	return (setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int)) ||
	setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(int)));
}

int					vm_socket_connect_wait(int sockfd,
					t_sockaddr *ai_addr, socklen_t ai_addrlen,
					int timeout)
{
	struct pollfd	fds;

	if (vm_socket_unblock(sockfd))
		return (-1);
	fds.fd = sockfd;
	fds.events = (POLLIN | POLLOUT | POLLHUP);
	printf("sock to connect %d with len %u\n", sockfd, ai_addrlen);
	if (connect(sockfd, ai_addr, ai_addrlen) < 0)
	{
		if (errno == EINPROGRESS)
		{
			poll(&fds, 1, timeout);
			if (fds.revents & (POLLHUP))
			{
				ft_printfd(2, "Error: connection has POLLHUP error\n");
				errno = 0;
				vm_socket_block(sockfd);
				return (-1);
			}
		}
	}
	else if (vm_socket_block(sockfd) < 0)
		return (-1);
	socket_setkeepalive(sockfd);
	return (0);
}
