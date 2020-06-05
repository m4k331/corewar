/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_manager_remove.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:30:36 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
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
		vm_worker_remove(input->worker_manager->workers[reg]);
	free(input->worker_manager->workers);
	free(input->worker_manager);
}
