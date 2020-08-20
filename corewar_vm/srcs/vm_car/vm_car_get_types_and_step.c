/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_car_get_types_and_step.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:57:44 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:57:44 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int32_t				vm_car_select_type_arg(uint8_t arg)
{
	if (arg == IND_CODE)
		return (T_IND);
	else if (arg == DIR_CODE)
		return (T_DIR);
	else if (arg == REG_CODE)
		return (T_REG);
	else
		return (0);
}

static int32_t		vm_car_len_by_type_arg(uint8_t type, t_ops op)
{
	if (type == T_REG)
		return (BSIZE_REG);
	else if (type == T_DIR)
		return (op.dir_size);
	else if (type == T_IND)
		return (BSIZE_IND);
	else
		return (0);
}

void				vm_car_get_types_and_step(t_ops op, uint8_t types_byte,
					int32_t args[6], t_car *car)
{
	int				i;

	i = 0;
	if (op.has_types)
	{
		car->step_size++;
		while (i < op.args_num)
		{
			args[i] =
				vm_car_select_type_arg((types_byte >> ((3 - i) * 2U)) & 3u);
			args[i + 3] = vm_car_len_by_type_arg(args[i], op);
			car->step_size += args[i + 3];
			i++;
		}
	}
	else
	{
		args[0] = op.args_types[0];
		args[3] = vm_car_len_by_type_arg(args[0], op);
		car->step_size += args[3];
	}
}
