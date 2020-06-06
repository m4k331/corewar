/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:48:30 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
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
