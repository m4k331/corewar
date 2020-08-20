/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_io_setup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:02:51 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:02:51 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_io_interface.h"

void				vm_socket_io_clean(t_io_interface *io)
{
	io->address = NULL;
	io->port = NULL;
	io->sock_fd = -1;
	io->error_tolerate = ERROR_TOLERATE;
}

t_io_interface		*vm_socket_io_init(void *superior)
{
	t_io_interface	*io;

	if (!(io = (t_io_interface*)malloc(sizeof(t_io_interface))))
	{
		ft_putstr_fd("Error: cant create io\n", 2);
		return (NULL);
	}
	vm_socket_io_clean(io);
	io->err_fd = 2;
	io->sock_fd = -1;
	io->cout = 1;
	io->superior = superior;
	io->netbuf = darr_init(NETBUF_INITLEN, 0, sizeof(uint8_t), NULL);
	return (io);
}
