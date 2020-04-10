/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_winner_notify.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:31:48 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:31:57 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_worker_winner_notify(t_worker *wk)
{
	int		winner;

	winner = -wk->last_lived - 1;
	ft_printfs(wk->log, "Player %d (%s) has won!\n",
			winner + 1, wk->champs[winner].name);
	ft_putstr_fd(wk->log->start, wk->io->cout);
	if (wk->gameid > 0)
		vm_message_endgame(wk);
	dstr_remove_front(wk->log, wk->log->len);
	wk->gameid = -1;
}
