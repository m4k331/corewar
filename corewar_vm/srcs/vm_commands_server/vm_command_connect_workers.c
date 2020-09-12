/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_connect_workers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:59:59 by limry             #+#    #+#             */
/*   Updated: 2020/07/04 15:29:11 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int			vm_command_connect_workers(t_io_interface *io)
{
	t_input	*super;
	int		wk_id;
	int		err_num;

	super = io->superior;
	wk_id = -1;
	while (++wk_id < ONLINE)
	{
		vm_worker_fill_io_interface(
				super->worker_mngr->workers[wk_id]->io, super, wk_id);
		if ((err_num =
				vm_socket_connect(super->worker_mngr->workers[wk_id]->io)))
		{
			ft_printfd(io->cout, "ERROR: can't connect worker %d", err_num);
			return (err_num);
		}
		ft_printfd(io->cout, "Worker #%d connected on %s:%s from %d\n", wk_id,
				super->worker_mngr->workers[wk_id]->io->address,
				super->worker_mngr->workers[wk_id]->io->port,
				super->worker_mngr->workers[wk_id]->io->sock_fd);
	}
	return (0);
}
