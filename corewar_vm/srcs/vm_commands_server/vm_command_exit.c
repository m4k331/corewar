/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:31:54 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 07:32:09 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void				vm_command_exit(t_io_interface *io)
{
	ft_printfd(io->cout, "Program is stopped\n");
	vm_exit("Good luck!\n", (t_input*)(io->superior));
}
