/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_receive_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:48:19 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 07:48:19 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"
#include "vm_game_input.h"

int		vm_input_recieve_data(t_input *input)
{
	int	res;

	res = 0;
	if (input->mode == ONLINE)
	{
		poll(input->fds, 2, TIMEOUT_INPUT);
		if ((input->fds[0].revents) & POLLIN)
			vm_input_listen_command(input);
		if ((input->fds[1].revents) & POLLIN)
			res = vm_input_socket_game_received(input);
		return (res);
	}
	else if (input->mode == OFFLINE)
	{
		vm_input_av_parse(input);
		return (1);
	}
	else
		return (0);
}
