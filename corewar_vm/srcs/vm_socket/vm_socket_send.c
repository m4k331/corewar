/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_send.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:04:59 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
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
	// TODO: delete
	ft_printf("Sended to %s:%s = %d bytes (fd:%d)\n", io->address, io->port, io->netbuf->len_data, io->sock_fd);
	darr_remove_front(io->netbuf, io->netbuf->len);
	return (sended);
}