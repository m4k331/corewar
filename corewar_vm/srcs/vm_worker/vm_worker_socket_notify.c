/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_socket_notify.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:31:36 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_worker_socket_notify(t_worker *wk)
{
	int		i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (wk->champs[i].name[0] != '\0')
		{
			ft_printfs(wk->log, MSG_PLAYER_PRESENTATION0,
					i + 1, wk->champs[i].code_size);
			ft_printfs(wk->log, MSG_PLAYER_PRESENTATION1,
					wk->champs[i].name, wk->champs[i].comment);
		}
	if (wk->gameid > 0)
		vm_message_game_loaded_notify(wk);
	ft_putstr_fd(wk->log->start, wk->io->cout);
	dstr_remove_front(wk->log, wk->log->len_data);
}
