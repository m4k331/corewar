/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:04:38 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:04:45 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

uint32_t			vm_socket_bytes_to_int(uint8_t *data_start, int32_t size)
{
	int				res;
	int				i;

	res = 0;
	if (size == 1)
		return ((int)data_start[0]);
	i = -1;
	while (++i < size)
		res |= (int)((data_start[i] & 0xFFU) << ((size - 1 - i) * 8u));
	return (res);
}

void				vm_socket_int_to_bytes(uint8_t *data_start,
					int num, int32_t size)
{
	int				i;

	i = -1;
	size = size > 4 ? 4 : size;
	while (++i < size)
		*(data_start + i) =
				(uint8_t)((num >> ((size - 1 - i) * 8U)) & 0xFF);
}
