/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_receive_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:00:41 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:00:41 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"
#include "vm_game_input.h"

int		vm_input_recieve_data(t_input *input)
{
	int	games_loaded;

	games_loaded = 0;
	if (input->mode == ONLINE)
	{
		poll(input->fds, 2, TIMEOUT_INPUT);
		if ((input->fds[0].revents) & POLLIN)
			vm_input_listen_command(input);
		if ((input->fds[1].revents) & POLLIN)
			games_loaded = vm_input_socket_is_game_received(input);
		return (games_loaded);
	}
	else if (input->mode == OFFLINE)
	{
		vm_input_av_parse(input);
		return (1);
	}
	else
		return (0);
}
