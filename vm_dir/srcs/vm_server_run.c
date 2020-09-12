/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_server_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:07:02 by limry             #+#    #+#             */
/*   Updated: 2020/07/04 15:52:25 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"
#include "vm_game_input.h"

uint32_t			vm_worker_get_id_of_free_worker(uint32_t reg_workers)
{
	uint32_t		id_of_free_worker;

	id_of_free_worker = 0;
	while ((reg_workers & 1u) != 1u)
	{
		reg_workers >>= 1u;
		if (++id_of_free_worker > ONLINE)
			return (ONLINE);
	}
	return (id_of_free_worker);
}

void				vm_server_run(t_input *input, pthread_attr_t *tattr)
{
	uint32_t		free_wk;
	int				flag;

	while (input->mode != 0)
	{
		flag = vm_input_recieve_data(input);
		if (flag && input->worker_mngr->reg_workers != 0 &&
			input->games_input_queue->len_data)
		{
			if (ONLINE != (free_wk = vm_worker_get_id_of_free_worker(
			input->worker_mngr->reg_workers)))
			{
				input->worker_mngr->reg_workers &= ~(1u << free_wk);
				vm_worker_get_data_from_queue(
				input->worker_mngr->workers[free_wk],
				input->games_input_queue);
				vm_message_game_loaded(input->worker_mngr->workers[free_wk],
						input);
				pthread_create(&(input->threads[free_wk]), tattr,
				vm_worker_run, (void*)(input->worker_mngr->workers[free_wk]));
			}
		}
		if (input->mode == OFFLINE)
			break ;
	}
}
