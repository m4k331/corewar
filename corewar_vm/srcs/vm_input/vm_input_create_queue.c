/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_create_queue.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:47:07 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
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
