/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_disconnect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:32:04 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static void	vm_diconnect_socket(t_io_interface *io)
{
	vm_socket_block(io->sock_fd);
	((t_input*)io->superior)->fds[1].fd = 0;
}

static void	vm_disconnect_workers(t_input *input)
{
	int		i;

	i = -1;
	while (++i < ONLINE)
	{
		vm_socket_disconnect(input->worker_manager->workers[i]->io);
		input->worker_manager->workers[i]->io->sock_fd = -1;
		free(input->worker_manager->workers[i]->io->port);
		vm_command_io_clean(input->worker_manager->workers[i]->io);
	}
}

int			vm_command_disconnect(t_io_interface *io)
{
	if (!io->address || !io->port)
	{
		ft_putstr_fd(ERR_SOCK_DISCONNECT, io->err_fd);
		return (CODE_ERR_SOCK_DISCONNECT);
	}
	vm_socket_disconnect(io);
	vm_command_io_clean(io);
	vm_disconnect_workers((t_input*)io->superior);
	vm_diconnect_socket(io);
	return (0);
}
