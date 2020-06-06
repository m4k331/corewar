/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_set_header.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:01:59 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_message_set_header(uint8_t type,
			int game_id, int len_msg, t_darr *buffer)
{
	uint8_t	buf[4];

	darr_remove_back(buffer, buffer->len);
	darr_join(buffer, (uint8_t*)&type, 1, sizeof(uint8_t));
	ft_bzero(&buf,4);
	vm_socket_int_to_bytes(buf, game_id, 4);
	darr_join(buffer, (uint8_t*)buf, 4, sizeof(uint8_t));
	ft_bzero(&buf,4);
	vm_socket_int_to_bytes(buf, len_msg, 4);
	darr_join(buffer, (uint8_t*)buf, 4, sizeof(uint8_t));
}
