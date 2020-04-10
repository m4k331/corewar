/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_set_header.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:01:59 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:01:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_message_set_header(uint8_t type,
			int game_id, int len_msg, t_darr *buffer)
{
	darr_remove_back(buffer, buffer->len);
	darr_join(buffer, (uint8_t*)&type, 1, sizeof(uint8_t));
	darr_join(buffer, (uint8_t*)&game_id, 4, sizeof(uint8_t));
	darr_join(buffer, (uint8_t*)&len_msg, 4, sizeof(uint8_t));
}
