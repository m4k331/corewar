/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_io_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:02:46 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:02:46 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_io_interface.h"

void		vm_socket_io_destroy(t_io_interface *io)
{
	if (!io)
		return ;
	if (io->netbuf)
		darr_delete(io->netbuf);
	free(io);
}
