/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_fork_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:04:59 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:04:59 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void			op_fork_set_pos_fork(t_car *car,
				t_car *from, int v1, t_worker *wk)
{
	ft_memcpy(car, from, sizeof(t_car));
	car->position = vm_get_addr(from->position + v1 % IDX_MOD);
	car->next = wk->live_head;
	car->id = ++wk->car_num;
	car->step_size = 0;
}

void			op_fork_set_pos_lfork(t_car *car,
				t_car *from, int v1, t_worker *wk)
{
	ft_memcpy(car, from, sizeof(t_car));
	car->position = vm_get_addr(from->position + v1);
	car->next = wk->live_head;
	car->id = ++wk->car_num;
	car->step_size = 0;
}

void			vm_fork_op_have_dead_head(t_worker *wk,
				t_car *car, int v[3], void (set_pos)(t_car *car,
				t_car *from, int v1, t_worker *wk))
{
	t_car		*rest_car;
	int32_t		tmp;

	rest_car = (t_car*)wk->carrs->data + wk->dead_head;
	tmp = wk->dead_head;
	wk->dead_head = rest_car->next;
	set_pos(rest_car, car, v[0], wk);
	wk->live_head = tmp;
}

t_car			*vm_fork_op_nop_dead_head(t_worker *wk,
				t_car *car, int *v, void (set_pos)(t_car *car,
				t_car *from, int v1, t_worker *wk))
{
	t_car		new_car;
	int32_t		tmp;

	set_pos(&new_car, car, v[0], wk);
	tmp = (t_car*)car - (t_car*)wk->carrs->data;
	darr_join(wk->carrs, &new_car, 1, sizeof(t_car));
	car = (t_car*)wk->carrs->data + tmp;
	wk->live_head = wk->carrs->len - 1;
	return (car);
}
