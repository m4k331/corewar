/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_car_implement_op.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:58:49 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:58:49 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int				vm_args_type_is_valid(t_ops op, int32_t args[6])
{
	int			i;

	if (op.has_types)
	{
		i = op.args_num;
		while (i--)
			if ((op.args_types[i] & args[i]) == 0)
				return (0);
	}
	return (1);
}

int				vm_args_define(int *arg, int *arg_len, uint8_t *cur_pos,
				t_ops op)
{
	int			reg;

	if (*arg == T_REG)
	{
		*arg_len += BSIZE_REG;
		if ((reg = *cur_pos) > REG_NUMBER || reg < 1)
			return (0);
	}
	else if (*arg == T_IND)
		*arg_len += BSIZE_IND;
	else if (*arg == T_DIR)
		*arg_len += op.dir_size;
	return (1);
}

int				vm_args_is_valid(t_car *car, t_worker *wk, int32_t args[6],
									t_ops op)
{
	int			len;
	int			i;
	uint32_t	flag;
	uint8_t		*cur_pos;

	len = op.has_types + 1;
	i = -1;
	flag = 1u;
	while (++i < op.args_num)
	{
		cur_pos = wk->map + vm_get_addr(car->position + len);
		flag &= vm_args_define(args + i, &len, cur_pos, op);
	}
	return (flag);
}

t_car			*vm_car_implement_op(t_car *car, t_worker *wk)
{
	int32_t		args_3t_3l[6];
	t_ops		op;

	op = wk->lib_ops[car->op_code - 1];
	ft_bzero(args_3t_3l, 24);
	vm_car_get_types_and_step(op,
	wk->map[vm_get_addr(car->position + 1)], args_3t_3l, car);
	if (vm_args_type_is_valid(op, args_3t_3l)
	&& vm_args_is_valid(car, wk, args_3t_3l, op))
		car = op.op(car, wk, args_3t_3l);
	vm_car_move(car, wk);
	return (car);
}
