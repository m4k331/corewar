/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_game_state_notify.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:03:47 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 22:55:59 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_worker_game_state_notify(t_worker *wk)
{
	if (wk->flag_log & LOG_MAP)
		vm_worker_show_map(wk, 64);
	if (wk->gameid > 0)
		vm_message_sendgame(wk);
}
