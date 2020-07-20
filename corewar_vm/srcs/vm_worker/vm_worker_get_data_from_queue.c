/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_get_data_from_queue.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:03:56 by limry             #+#    #+#             */
/*   Updated: 2020/07/04 16:00:31 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_game_input.h"
#include "vm_server.h"

static void		vm_worker_add_player_id(t_worker **worker,
				int i, t_gminput input, int j)
{
	(*worker)->gameid = input.game_id;
	ft_memcpy((*worker)->champs[j].name,
			input.players[i].name, PROG_NAME_LENGTH + 1);
	ft_memcpy((*worker)->champs[j].comment,
			input.players[i].comment, COMMENT_LENGTH + 1);
	(*worker)->champs[j].code_size = input.players[i].code_size;
}

static void		vm_worker_prep_for_init_data(int *i, int *j, t_car *car,
				t_worker *worker)
{
	*i = -1;
	*j = -1;
	ft_bzero(car, sizeof(t_car));
	vm_worker_clean(worker);
}

void			vm_worker_init_game(t_worker *worker, t_gminput input)
{
	int			i;
	int			j;
	int			zone;
	t_car		car;

	vm_worker_prep_for_init_data(&i, &j, &car, worker);
	zone = MEM_SIZE / input.num_players;
	while (++i < MAX_PLAYERS)
		if (input.players[i].id != 0 && ++j + 1)
		{
			vm_worker_add_player_id(&worker, i, input, j);
			ft_memcpy(worker->map + j * zone,
					input.players[i].code, input.players[i].code_size);
			ft_memset(worker->set + j * zone,
					input.players[i].id, input.players[i].code_size);
			car.reg[0] = -i - 1;
			car.position = j * zone;
			car.next = !j ? -1 : (j - 1);
			car.id = ++worker->car_num;
			car.last_live = 0;
			worker->last_lived = -j - 1;
			darr_join(worker->carrs, &car, 1, sizeof(t_car));
		}
	worker->live_head = j;
}

void			vm_worker_get_data_from_queue(t_worker *worker,
				t_darr *vm_input_queue)
{
	t_gminput	game;

	if (vm_input_queue->len_data == 0)
		return ;
	darr_pop_front_wo_mal(vm_input_queue, (void*)&game, 1);
	vm_worker_init_game(worker, game);
	if (game.game_id > 0)
		ft_printf("LOADING GAME #%u (in worker %u)\n",
			game.game_id, worker->gameid);
}
