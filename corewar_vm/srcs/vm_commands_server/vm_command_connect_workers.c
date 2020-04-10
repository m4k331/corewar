/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_connect_workers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:32:16 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 07:32:17 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int			vm_command_connect_workers(t_io_interface *io)
{
	t_input	*super;
	int		wk_id;

	super = io->superior;
	wk_id = -1;
	while (++wk_id < ONLINE)
	{
		vm_worker_fill_io_interface(
		super->worker_manager->workers[wk_id]->io, super, wk_id);
		vm_socket_connect(super->worker_manager->workers[wk_id]->io);
	}
	return (0);
}
