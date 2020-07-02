/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_log_dead_proc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:04:01 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:04:01 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void			vm_worker_log_dead_proc(t_worker *wk)
{
	if (wk->flag_log & LOG_DEATH)
		ft_putstr_fd(wk->log->start, wk->io->cout);
	if (wk->gameid > 0)
		vm_message_proc_statuses(wk);
	dstr_remove_front(wk->log, wk->log->len);
}
