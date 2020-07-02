/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_connect_wait.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:02:27 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:02:27 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int					vm_socket_connect_wait(int sockfd,
					struct sockaddr *ai_addr, socklen_t ai_addrlen,
					int timeout)
{
	struct pollfd	fds;

	if (vm_socket_unblock(sockfd))
		return (-1);
	fds.fd = sockfd;
	fds.events = (POLLIN | POLLOUT | POLLHUP);
	if (connect(sockfd, ai_addr, ai_addrlen) < 0)
	{
		if (errno == EINPROGRESS)
		{
			poll(&fds, 1, timeout);
			if (fds.revents & (POLLHUP))
			{
				ft_printfd(2, "Error: connect is POLLHUP\n");
				errno = 0;
				vm_socket_block(sockfd);
				return (-1);
			}
		}
	}
	else if (vm_socket_block(sockfd) < 0)
		return (-1);
	return (0);
}
