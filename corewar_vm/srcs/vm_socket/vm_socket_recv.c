/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_recv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:05:10 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_io_interface.h"

int					vm_socket_receive_data(t_io_interface *io,
					int32_t size_read_bytes)
{
	int				total;
	int				read_bytes;
	int				left;

	if (size_read_bytes < 1)
		return (-1);
	total = 0;
	left = size_read_bytes;
	while (left)
	{
		if ((read_bytes = recv(io->sock_fd,
		(uint8_t*)io->netbuf->start + io->netbuf->len_data, left, 0)) == -1)
		{
			ft_printfd(io->err_fd, "Error: %d is not enough data\n", total +
			read_bytes);
			darr_remove_front(io->netbuf, io->netbuf->len);
			return (0);
		}
		total += read_bytes;
		left -= read_bytes;
	}
	ft_printfd(io->cout, "Receive  %d bytes from %s:%s\n",
			total, io->address, io->port);
	return (total);
}

int					vm_socket_recv_timeout(int fd,
					char buf[MAXDATASIZE], uint32_t len, uint32_t timeout)
{
	struct pollfd	fds;
	int				ret;
	int				code;

	fds.fd = fd;
	fds.events = POLLIN;
	len = len > MAXDATASIZE ? MAXDATASIZE : len;
	if (-1 == (code = poll(&fds, 1, timeout)))
		return (-2);
	else if (!code)
		return (code);
	else
	{
		if (fds.revents & POLLIN)
		{
			if (0 < (ret = recv(fd, buf, len, 0)))
				return (ret);
			else
				return (-1);
		}
		else
			return (-1);
	}
}

int					vm_socket_receive_data_wait(t_io_interface *io,
					int32_t size_read_bytes)
{
	int				total;
	int				read;
	int				left;
	char			buf[MAXDATASIZE];

	total = 0;
	left = size_read_bytes;
	vm_socket_unblock(io->sock_fd);
	while (left > 0)
	{
		if ((read = vm_socket_recv_timeout(io->sock_fd, buf, left,
				TIMEOUT_RECV)) < 0)
		{
			ft_printfd(io->err_fd, ERR_SOCK_RECV, total + read);
			darr_remove_front(io->netbuf, io->netbuf->len);
			return (0);
		}
		darr_join(io->netbuf, buf, read, sizeof(uint8_t));
		total += read;
		left -= read;
	}
	vm_socket_block(io->sock_fd);
	if (size_read_bytes > 0)
		ft_printfd(io->cout, MSG_SOCK_RECV, total, io->address, io->port);
	return (total);
}
