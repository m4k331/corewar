/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_socket_notify.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:03:35 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:03:35 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_worker_socket_notify(t_worker *wk)
{
	int		i;

	i = -1;
	dstr_remove_back(wk->log, wk->log->len);
	while (++i < MAX_PLAYERS)
		if (wk->champs[i].name[0] != '\0')
		{
			ft_printfs(wk->log, MSG_PLAYER_PRESENTATION0,
					i + 1, wk->champs[i].code_size);
			ft_printfs(wk->log, MSG_PLAYER_PRESENTATION1,
					wk->champs[i].name, wk->champs[i].comment);
		}
	if (wk->gameid > 0)
		vm_message_champs_present(wk);
	ft_putstr_fd(wk->log->start, wk->io->cout);
	dstr_remove_front(wk->log, wk->log->len_data);
}
