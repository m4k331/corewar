/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_connect_workers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:32:16 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
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
		super->worker_manager->workers[wk_id]->io, super, wk_id);
		if ((err_num = vm_socket_connect(
				super->worker_manager->workers[wk_id]->io)))
		{
			ft_printfd(io->cout, "ERROR: %d", err_num);
			return (err_num);
		}
		ft_printfd(io->cout, "Worker #%d connected on %s:%s from %d\n", wk_id,
				super->worker_manager->workers[wk_id]->io->address,
				super->wk_sockets[wk_id],
				super->worker_manager->workers[wk_id]->io->sock_fd);
	}
	return (0);
}
