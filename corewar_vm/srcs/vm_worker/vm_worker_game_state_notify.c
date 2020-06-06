/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_game_state_notify.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:29:02 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
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
