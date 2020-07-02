/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_game_loaded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:01:55 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:01:55 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_message_game_loaded(t_worker *wk, t_input *input)
{
	int		port;

	if (input->mode == OFFLINE)
		return ;
	port = ft_atoi(wk->io->port);
	vm_message_set_header(TYPE_GAME_LOADED,
	wk->gameid, 4, input->io->netbuf);
	vm_socket_int_to_bytes((uint8_t*)input->io->netbuf->start, port, 4);
	vm_socket_send_buff(input->io);
}
