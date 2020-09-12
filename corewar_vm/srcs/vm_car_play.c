/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_car_play.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:58:40 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:58:40 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int			vm_car_move_log(t_car *car, t_worker *wk)
{
	int		new_pos;
	int		i;

	new_pos = vm_get_addr(car->position + car->step_size);
	dstr_remove_front(wk->log, wk->log->len_data);
	ft_printfs(wk->log, "car %d with step %d (%#06x - %#06x)",
			car->id, car->step_size, car->position, new_pos);
	i = car->position;
	while (i < new_pos)
		ft_printfs(wk->log, " %02x", wk->map[i++]);
	ft_printfs(wk->log, "\n");
	ft_putstr_fd(wk->log->start, wk->io->cout);
	dstr_remove_front(wk->log, wk->log->len_data);
	return (new_pos);
}

void		vm_car_move(t_car *car, t_worker *wk)
{
	int		new_pos;

	if (wk->flag_log & LOG_MOVE && car->step_size > 1)
		new_pos = vm_car_move_log(car, wk);
	else
		new_pos = vm_get_addr(car->position + car->step_size);
	car->position = new_pos;
	car->step_size = 0;
}

void		vm_car_load_op(t_car *car, t_worker *worker)
{
	car->op_code = worker->map[car->position];
	if (++car->step_size && car->op_code >= 0x01 && car->op_code <= 0x10)
		car->program_counter = worker->lib_ops[car->op_code - 1].counter;
	else
		vm_car_move(car, worker);
}

t_car		*vm_car_play(t_car *car, t_worker *worker)
{
	if (car->program_counter == 0)
		vm_car_load_op(car, worker);
	if (car->program_counter > 0)
		if (--(car->program_counter) == 0)
			car = vm_car_implement_op(car, worker);
	return (car);
}
