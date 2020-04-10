/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_send.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:04:59 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:05:04 by kona             ###   ########.fr       */
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
	while (left)
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
	darr_remove_front(io->netbuf, io->netbuf->len);
	return (sended);
}
