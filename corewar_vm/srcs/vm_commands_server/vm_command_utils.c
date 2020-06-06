/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:31:11 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int			vm_command_check_args(char *args, t_io_interface *io)
{
	if (!args)
	{
		ft_printfd(io->err_fd, ERR_NOT_ENOUGH_ARGS0, io->command);
		ft_putstr_fd(ERR_NOT_ENOUGH_ARGS1, io->err_fd);
		return (CODE_ERR_NOT_ENOUGH_ARGS);
	}
	return (0);
}

int			vm_command_not_exists(t_io_interface *io)
{
	ft_printfd(io->err_fd, ERR_COMMAND, io->command);
	return (CODE_ERR_COMMAND);
}

void		vm_connect_socket_setup(t_io_interface *io)
{
	vm_socket_unblock(io->sock_fd);
	((t_input*)io->superior)->fds[1].fd = io->sock_fd;
	((t_input*)io->superior)->fds[1].events = POLLIN;
}
