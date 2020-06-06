/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_disconnect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:06:28 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
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
