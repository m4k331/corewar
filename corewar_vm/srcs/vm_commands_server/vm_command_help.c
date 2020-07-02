/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:59:37 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:59:37 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int					vm_command_help(t_io_interface *io)
{
	ft_printfd(io->cout, MSG_HELP0);
	ft_printfd(io->cout, MSG_HELP1);
	ft_printfd(io->cout, MSG_HELP2);
	ft_printfd(io->cout, MSG_HELP3);
	ft_printfd(io->cout, MSG_HELP4);
	ft_printfd(io->cout, MSG_HELP5);
	ft_printfd(io->cout, MSG_HELP6);
	ft_printfd(io->cout, MSG_HELP7);
	ft_printfd(io->cout, MSG_HELP8);
	return (CODE_MSG_HELP);
}

int					vm_command_help_log(t_io_interface *io)
{
	ft_printfd(io->cout, MSG_HELP_LOG0);
	ft_printfd(io->cout, MSG_HELP_LOG1);
	ft_printfd(io->cout, MSG_HELP_LOG2);
	ft_printfd(io->cout, MSG_HELP_LOG3);
	ft_printfd(io->cout, MSG_HELP_LOG4);
	ft_printfd(io->cout, MSG_HELP_LOG5);
	ft_printfd(io->cout, MSG_HELP_LOG6);
	return (CODE_MSG_HELP_LOG);
}
