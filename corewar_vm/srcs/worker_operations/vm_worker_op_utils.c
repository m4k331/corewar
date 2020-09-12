/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_op_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:04:53 by limry             #+#    #+#             */
/*   Updated: 2020/09/11 17:43:21 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int			vm_op_byte_to_32int(uint8_t *data_start, int32_t pos, int32_t size)
{
	int		res;
	uint8_t	sign;
	int		i;

	pos = vm_get_addr(pos);
	sign = data_start[pos] & 0x80u;
	res = 0;
	i = -1;
	if (size == 1)
		return (data_start[pos]);
	while (++i < size)
		if (sign)
			res |= (int)((data_start[vm_get_addr(pos + i)]
					^ 0xFFU) << ((size - 1 - i) * 8u));
		else
			res |= (int)((data_start[vm_get_addr(pos + i)]
					& 0xFFU) << ((size - 1 - i) * 8u));
	if (sign)
		res = 0 - (res + 1);
	return (res);
}

void		vm_op_from_int32_to_byte(uint8_t *data_start, int num,
			int32_t pos, int32_t size)
{
	int		i;

	i = -1;
	pos = vm_get_addr(pos);
	while (++i < size)
		*(data_start + vm_get_addr(pos + i)) =
		(uint8_t)((num >> ((size - 1 - i) * 8U)) & 0xFFu);
}

void		vm_op_set_val_to_byte(uint8_t *data_start, uint8_t setter,
			int32_t pos, int32_t size)
{
	int		i;

	i = -1;
	pos = vm_get_addr(pos);
	while (++i < size)
		*(data_start + vm_get_addr(pos + i)) =
				(uint8_t)(setter & 0xFFu);
}

int32_t		vm_get_addr(int32_t address)
{
	address %= MEM_SIZE;
	return (address < 0 ? address + MEM_SIZE : address);
}

int			vm_op_get_val(t_worker *wk, t_car *car,
			const int *arg, int offset_cut[2])
{
	int		res;

	res = vm_op_byte_to_32int(wk->map,
	vm_get_addr(car->position + offset_cut[0]), *(arg + 3));
	if (*arg == T_REG)
		res = car->reg[res - 1];
	else if (*arg == T_IND)
		res = vm_op_byte_to_32int(wk->map, vm_get_addr(car->position +
		(offset_cut[1] ? (res % IDX_MOD) : res)), DIR_SIZE);
	return (res);
}
