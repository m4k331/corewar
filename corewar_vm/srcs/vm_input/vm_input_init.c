/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:00:59 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:00:59 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void			vm_input_clean_wk_sockets(t_input *input)
{
	int			i;

	i = -1;
	while (++i < ONLINE)
		input->wk_sockets[i] = NULL;
}

t_input			*vm_init_input(int ac, char **av)
{
	t_input *input;

	if (!(input = (t_input*)malloc(sizeof(t_input))))
		return (NULL);
	ft_bzero(input, sizeof(t_input));
	input->flag_dump = -1;
	input->ac = ac;
	input->av = av;
	input->console_buffer = dstr_init(NULL, 20);
	input->io = vm_socket_io_init((void *)input);
	vm_input_clean_wk_sockets(input);
	return (input);
}
