/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_send.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:03:02 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:03:02 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_io_interface.h"

int			vm_socket_send(int fd, void *data, int num_bytes)
{
	int		total;
	int		left;
	int		sended;

	total = 0;
	left = num_bytes;
	sended = 0;
	while (left > 0)
	{
		sended = send(fd, (uint8_t*)data + total,
					left, 0);
		if (sended == -1)
			break ;
		total += sended;
		left -= sended;
	}
	return (sended < 0 ? -1 : total);
}

int			vm_socket_send_buff(t_io_interface *io)
{
	int		sended;

	sended = vm_socket_send(io->sock_fd,
		io->netbuf->start, io->netbuf->len_data);
	ft_printf("Sended to %s:%s = %d bytes (fd:%d)\n",
			io->address, io->port, io->netbuf->len_data, io->sock_fd);
	darr_remove_front(io->netbuf, io->netbuf->len);
	return (sended);
}
