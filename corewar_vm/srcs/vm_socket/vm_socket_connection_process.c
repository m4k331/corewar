/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_connection_process.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:02:33 by limry             #+#    #+#             */
/*   Updated: 2020/09/08 18:48:49 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_io_interface.h"

static int				vm_socket_connection_processing(
						t_addrinfo *servinfo, t_io_interface *io)
{
	int					sockfd;

	if (!servinfo)
		return (1);
	sockfd = -1;
	while (servinfo)
	{
		if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
				servinfo->ai_protocol)) == -1)
			ft_printfd(io->err_fd, "Error: can't get socket\n");
		else if (!vm_socket_connect_wait(sockfd, servinfo->ai_addr,
				servinfo->ai_addrlen, TIMEOUT_CONNECT))
			break ;
		if (sockfd != -1)
		{
			ft_printfd(io->err_fd, "Error: can't connect sock %d\n", sockfd);
			close(sockfd);
		}
		servinfo = servinfo->ai_next;
	}
	if (!servinfo)
		return (2);
	io->sock_fd = sockfd;
	return (0);
}

static void				*get_in_addr(t_sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return (&(((struct sockaddr_in*)sa)->sin_addr));
	return (&(((struct sockaddr_in6*)sa)->sin6_addr));
}

static in_port_t		get_in_port(t_sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return (((struct sockaddr_in*)sa)->sin_port);
	return (((struct sockaddr_in6*)sa)->sin6_port);
}

static t_addrinfo		*vm_connection_getservinfo(t_io_interface *io,
						t_addrinfo **servinfo)
{
	int					rv;

	if ((rv = getaddrinfo(io->address, io->port,
					&(io->hints), servinfo)))
	{
		ft_printfd(io->err_fd, "getaddrinfo: %s\n", gai_strerror(rv));
		vm_socket_io_clean(io);
		return (NULL);
	}
	io->sock_fd = get_in_port((*servinfo)->ai_addr);
	ft_printfd(io->err_fd, "Assigned port is %d\n",
			io->sock_fd);
	return (*servinfo);
}

int						vm_socket_connect(t_io_interface *io)
{
	t_addrinfo			*servinfo;
	char				s[INET6_ADDRSTRLEN];

	if (!vm_connection_getservinfo(io, &servinfo))
	{
		ft_printfd(io->err_fd, ERR_CONNECTION);
		return (CODE_ERR_CONNECTION);
	}
	if ((vm_socket_connection_processing(servinfo, io)))
	{
		ft_printfd(io->err_fd, ERR_ADDR, io->address, io->port);
		vm_socket_io_clean(io);
		freeaddrinfo(servinfo);
		return (CODE_ERR_ADDR);
	}
	else
	{
		inet_ntop(servinfo->ai_family,
		get_in_addr((struct sockaddr*)servinfo->ai_addr), s, sizeof(s));
		ft_printfd(io->cout, "VM: connecting to %s\n", s);
	}
	freeaddrinfo(servinfo);
	return (0);
}
