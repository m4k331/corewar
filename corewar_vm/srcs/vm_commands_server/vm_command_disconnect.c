/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_disconnect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:59:54 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:59:54 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static void	vm_diconnect_socket_fds(t_io_interface *io)
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
		vm_socket_disconnect(input->worker_mngr->workers[i]->io);
		input->worker_mngr->workers[i]->io->sock_fd = -1;
		free(input->worker_mngr->workers[i]->io->port);
		vm_command_io_clean(input->worker_mngr->workers[i]->io);
	}
}

int			vm_command_disconnect(t_io_interface *io)
{
	if (!io->address || !io->port)
	{
		ft_putstr_fd(ERR_SOCK_DISCONNECT, io->err_fd);
		return (CODE_ERR_SOCK_DISCONNECT);
	}
	ft_printfd(io->cout, "Disconnection from hub %s:%s \n",
			io->address, io->port);
	vm_socket_disconnect(io);
	vm_command_io_clean(io);
	vm_disconnect_workers((t_input*)io->superior);
	vm_diconnect_socket_fds(io);
	ft_putstr_fd("Disconnection completed\n", io->cout);
	return (0);
}
