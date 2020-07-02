/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:05:52 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:05:52 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static void		vm_worker_send_msg(t_worker *wk, t_car *car)
{
	if (wk->flag_log & 4)
		ft_putstr_fd(wk->log->start, wk->io->cout);
	if (wk->gameid > 0)
	{
		vm_message_operation(wk, car);
		vm_socket_send_buff(wk->io);
		dstr_remove_front(wk->log, wk->log->len);
	}
	dstr_remove_front(wk->log, wk->log->len_data);
}

static int		vm_op_spec_ops(t_car *car, t_worker *wk, int *v)
{
	int			worked;

	worked = 0;
	if (car->op_code == 12 && ++worked)
		ft_printfs(wk->log, "%d (%d)\n",
				v[0] % IDX_MOD, car->position + v[0]);
	else if (car->op_code == 15 && ++worked)
		ft_printfs(wk->log, "%d (%d)\n",
				v[0], car->position + v[0]);
	else if (car->op_code == 9 && ++worked)
	{
		if (car->carry)
			ft_printfs(wk->log, "%d OK\n", v[0]);
		else
			ft_printfs(wk->log, "%d FAILED\n", v[0]);
	}
	return (worked);
}

void			vm_op_log(t_car *car, int v[3],
				int ar_3t_3l[6], t_worker *wk)
{
	t_ops		op;
	int			i;

	op = wk->lib_ops[car->op_code - 1];
	ft_printfs(wk->log, "P % 4d | %s ", car->id, op.name);
	i = 0;
	if (!vm_op_spec_ops(car, wk, v))
		while (i < op.args_num)
		{
			if (ar_3t_3l[i] == T_REG)
				ft_printfs(wk->log, "r%d", v[i++]);
			else if (ar_3t_3l[i] == T_DIR)
				ft_printfs(wk->log, "%d", v[i++]);
			else if (ar_3t_3l[i] == T_IND)
				ft_printfs(wk->log, "%%%d", v[i++]);
			if (i == op.args_num)
				ft_printfs(wk->log, "\n");
			else
				ft_printfs(wk->log, " ");
		}
	vm_worker_send_msg(wk, car);
}
