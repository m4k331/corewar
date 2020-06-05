/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_game_loaded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:51:31 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 00:38:52 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_message_game_loaded(t_worker *wk, t_input *input)
{
	int		port;

	port = ft_atoi(wk->io->port);
	vm_message_set_header(TYPE_GAME_LOADED,
	wk->gameid, 4, input->io->netbuf);
	vm_socket_int_to_bytes((uint8_t*)input->io->netbuf->start, port, 4);
//	darr_join(input->io->netbuf, (uint8_t*)buf, 4, sizeof(uint8_t));
	vm_socket_send_buff(input->io);
}