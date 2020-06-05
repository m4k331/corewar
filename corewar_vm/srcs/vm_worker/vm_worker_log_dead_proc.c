/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_log_dead_proc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:29:28 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
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
