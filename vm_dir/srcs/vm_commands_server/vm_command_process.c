/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:59:31 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:59:31 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static int			vm_command_parse2(char *args, t_io_interface *io,
					int *err_no)
{
	if (!ft_strcmp(io->command, "wklog"))
		*err_no = vm_command_wksetlog(args, io);
	else if (!ft_strcmp(io->command, "disconnect"))
		*err_no = vm_command_disconnect(io);
	else if (!ft_strcmp(io->command, "reconnect"))
	{
		if ((*err_no = vm_command_disconnect(io)))
			return (*err_no);
		vm_command_io_clean(io);
		*err_no = vm_command_connect(args, io);
	}
	else if (!ft_strcmp(io->command, "status"))
		*err_no = vm_command_status(io);
	else
		*err_no = vm_command_not_exists(io);
	return (*err_no);
}

static int			vm_command_parse(char *args, t_io_interface *io)
{
	int				err_no;

	err_no = 0;
	if (!ft_strcmp(io->command, "connect"))
		err_no = vm_command_connect(args, io);
	else if (!ft_strcmp(io->command, "help") ||
			!ft_strcmp(io->command, "h"))
		err_no = vm_command_help(io);
	else if (!ft_strcmp(io->command, "help_log") ||
			!ft_strcmp(io->command, "hl"))
		err_no = vm_command_help_log(io);
	else if (!ft_strcmp(io->command, "stop") ||
			!ft_strcmp(io->command, "exit"))
		vm_command_exit(io);
	else
		return (vm_command_parse2(args, io, &err_no));
	return (err_no);
}

static int			vm_socket_command_implement(t_io_interface *io,
					t_dstr *cons_input)
{
	char			*args;
	int				code;

	io->command = cons_input->start;
	args = ft_strchr(cons_input->start, ' ');
	if (!io->command)
	{
		ft_printfd(io->err_fd, "Error: enter any of available command\n");
		return (CODE_ERR_NOT_ENOUGH_ARGS);
	}
	if (args)
	{
		*args = '\0';
		args++;
	}
	if ((code = vm_command_parse(args, io)))
		return (code);
	return (0);
}

int					vm_input_listen_command(t_input *input)
{
	char			c;

	c = 0;
	while ((0 < read(0, &c, 1)))
	{
		if (c == '\n')
			break ;
		dstr_joinstr_len(input->console_buffer, &c, 1);
	}
	if (c == '\n')
	{
		vm_socket_command_implement(input->io, input->console_buffer);
		dstr_remove_front(input->console_buffer, input->console_buffer->len);
	}
	return (input->mode == ONLINE ? -1 : 0);
}
