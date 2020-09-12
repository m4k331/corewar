/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:04:15 by limry             #+#    #+#             */
/*   Updated: 2020/07/04 15:50:54 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_game_input.h"
#include "vm_server.h"

void			vm_worker_dead_proc(t_worker *wk, t_car *tmp, t_car *tmp_prev)
{
	if ((t_car*)wk->carrs->data + wk->live_head == tmp)
		wk->live_head = tmp->next;
	else
		tmp_prev->next = tmp->next;
	tmp->next = wk->dead_head;
	wk->dead_head = (t_car*)tmp - (t_car*)wk->carrs->data;
	if (wk->flag_log & LOG_DEATH || wk->gameid > 0)
		ft_printfs(wk->log, "Process %d is dead\n", tmp->id);
}

void			vm_worker_check_cars(t_worker *wk)
{
	t_car		*tmp;
	t_car		*tmp_prev;
	int32_t		flag_dead_proc;
	int32_t		next;

	tmp = (t_car*)wk->carrs->data + wk->live_head;
	tmp_prev = NULL;
	while (tmp)
	{
		flag_dead_proc = 0;
		next = tmp->next;
		if ((tmp->last_live <= wk->cur_ctd - wk->ctd || wk->ctd <= 0)
		&& ++flag_dead_proc)
			vm_worker_dead_proc(wk, tmp, tmp_prev);
		if ((next == -1) || wk->live_head == -1)
			break ;
		tmp_prev = (!flag_dead_proc || !tmp_prev) ? tmp : tmp_prev;
		tmp = (t_car*)wk->carrs->data + next;
	}
}

void			vm_worker_check_cycle(t_worker *worker)
{
	vm_worker_check_cars(worker);
	vm_worker_log_dead_proc(worker);
	worker->num_checks++;
	if (worker->num_live / NBR_LIVE > 0 ||
		worker->num_checks == MAX_CHECKS)
	{
		worker->ctd -= CYCLE_DELTA;
		worker->num_checks = 0;
	}
	worker->num_live = 0;
}

int				vm_worker_run_cycle(t_worker *worker)
{
	int			i;
	t_car		*car;

	i = worker->ctd < 0 ? 1 : worker->ctd;
	while (i-- && worker->live_head != -1)
	{
		worker->cur_ctd++;
		if (worker->flag_log & LOG_CYCLE)
			ft_printfd(worker->io->cout, "It is now cycle %d\n",
					worker->cur_ctd);
		vm_worker_game_state_notify(worker);
		car = (t_car*)worker->carrs->data + worker->live_head;
		while (car)
		{
			car = vm_car_play(car, worker);
			if (car->next == -1)
				break ;
			car = (t_car*)worker->carrs->data + car->next;
		}
		if (worker->dump == worker->cur_ctd)
			return (vm_worker_show_map(worker, 32));
	}
	return (0);
}

void			*vm_worker_run(void *wk)
{
	t_worker	*worker;

	worker = (t_worker*)wk;
	vm_worker_socket_notify(worker);
	if (worker->dump == 0)
	{
		vm_worker_show_map(worker, 32);
		return (NULL);
	}
	while (worker->live_head != -1)
	{
		if (vm_worker_run_cycle(worker))
			break ;
		vm_worker_check_cycle(worker);
	}
	if (worker->dump == -1)
		vm_worker_winner_notify(worker);
	*(worker->reg_workers) |= (1u << (worker->id_worker));
	pthread_exit(NULL);
}
