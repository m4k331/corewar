/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:31:25 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 07:31:25 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int			vm_command_status(t_io_interface *io)
{
	if (io->address && io->port)
		ft_printfd(io->cout, MSG_STATUS_SERVER, io->address, io->port);
	else
		ft_printfd(io->cout, "VM is not connected");
	return (0);
}
