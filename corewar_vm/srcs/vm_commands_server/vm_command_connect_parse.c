/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_connect_parse.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:00:04 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:00:04 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static int			vm_connect_check_args(t_io_interface *io)
{
	if (io->port[0] == '\0' ||
		io->address[0] == '\0')
	{
		vm_command_io_clean(io);
		ft_printfd(io->err_fd, ERR_WRONG_ADDR_OR_PORT);
		return (CODE_ERR_WRONG_ADDR_OR_PORT);
	}
	return (0);
}

static int			vm_connect_too_many_args(t_io_interface *io, char *args)
{
	if (args != NULL)
	{
		vm_command_io_clean(io);
		ft_printfd(io->err_fd, ERR_MANY_ARGS, args);
		return (CODE_ERR_MANY_ARGS);
	}
	return (0);
}

static int			vm_connect_get_address(t_io_interface *io, char *args)
{
	int				err_num;

	if ((err_num = vm_command_check_args(args, io)))
	{
		vm_command_io_clean(io);
		return (err_num);
	}
	io->address = args;
	return (0);
}

static int			vm_connect_get_port(t_io_interface *io, char *args)
{
	int				err_num;

	if ((err_num = vm_command_check_args(args, io)))
	{
		vm_command_io_clean(io);
		return (err_num);
	}
	*args = '\0';
	io->port = args + 1;
	return (0);
}

int					vm_command_connect_parse(char *args, t_io_interface *io)
{
	int				err_num;

	if (io->address && io->port)
		return (vm_nofity_err(io->err_fd, ERR_ALRDY_CNTD, CD_ERR_ALRDY_CNTD));
	if ((err_num = vm_connect_get_address(io, args)))
		return (err_num);
	args = ft_strchr(io->address, ' ');
	if ((err_num = vm_connect_get_port(io, args)))
		return (err_num);
	args = ft_strchr(io->port, ' ');
	if ((err_num = vm_connect_check_args(io)))
		return (err_num);
	if ((err_num = vm_connect_too_many_args(io, args)))
		return (err_num);
	if ((err_num = vm_socket_connect(io)))
		return (err_num);
	if ((err_num = vm_command_handshake_send(io)))
		return (err_num);
	if ((err_num = vm_command_handshake_recv(io)))
		return (err_num);
	if ((err_num = vm_command_connect_workers(io)))
		return (err_num);
	vm_connect_socket_setup(io);
	return (0);
}
