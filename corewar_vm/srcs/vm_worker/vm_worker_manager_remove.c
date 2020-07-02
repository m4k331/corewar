/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_manager_remove.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:04:11 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:04:11 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_game_input.h"

void		vm_worker_remove(t_worker *wk)
{
	vm_socket_io_destroy(wk->io);
	wk->io = NULL;
	dstr_del(wk->log);
	wk->log = NULL;
	darr_delete(wk->carrs);
	wk->carrs = NULL;
	free(wk);
	wk = NULL;
}

void		vm_worker_manager_remove(t_input *input)
{
	int		reg;

	reg = input->mode < 0 ? -input->mode : input->mode;
	while (reg--)
		vm_worker_remove(input->worker_mngr->workers[reg]);
	free(input->worker_mngr->workers);
	free(input->worker_mngr);
}
