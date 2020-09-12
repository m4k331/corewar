/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:00:35 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:00:35 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_remove_sockets(t_input *input)
{
	int		i;

	i = -1;
	while (++i < ONLINE)
		free(input->wk_sockets[i]);
}

void		vm_input_remove(t_input *input)
{
	if (input)
	{
		if (input->io)
			vm_socket_io_destroy(input->io);
		darr_delete(input->games_input_queue);
		dstr_del(input->console_buffer);
		vm_remove_sockets(input);
		free(input->threads);
	}
	free(input);
}
