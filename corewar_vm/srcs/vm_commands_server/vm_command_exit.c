/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:59:49 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:59:49 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void				vm_command_exit(t_io_interface *io)
{
	ft_printfd(io->cout, "Program is stopped\n");
	vm_exit("Good luck!\n", (t_input*)(io->superior));
}
