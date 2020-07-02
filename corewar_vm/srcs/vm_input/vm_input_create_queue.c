/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_create_queue.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:58:16 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:58:16 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_game_input.h"

void			vm_input_create_queue(t_input *input)
{
	uint64_t	num_games;

	num_games = input->mode < 0 ? (uint64_t)-input->mode :
			(uint64_t)input->mode;
	input->games_input_queue = darr_init((uint64_t)num_games, 0,
			sizeof(t_gminput), NULL);
}
