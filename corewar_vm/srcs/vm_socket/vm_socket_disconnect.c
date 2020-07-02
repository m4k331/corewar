/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_disconnect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:02:37 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:02:37 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int		vm_socket_disconnect(t_io_interface *io)
{
	if (!io->address || !io->port)
	{
		ft_putstr_fd(ERR_SOCK_DISCONNECT, io->err_fd);
		return (CODE_ERR_SOCK_DISCONNECT);
	}
	vm_socket_close(io->sock_fd, io);
	return (0);
}
