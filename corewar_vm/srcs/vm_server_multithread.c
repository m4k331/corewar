/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_server_multithread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:20:51 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:33 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_server_thread_attr_set(pthread_attr_t *tattr, int mode)
{
	pthread_attr_init(tattr);
	if (mode == ONLINE)
		pthread_attr_setdetachstate(tattr, PTHREAD_CREATE_DETACHED);
}

void		vm_server_wait_for_threads(t_input *input, int mode)
{
	int		reg;
	int		i;

	if (mode == ONLINE)
		return ;
	reg = input->mode < 0 ? -input->mode : ONLINE;
	i = -1;
	while (++i < reg)
		pthread_join(input->threads[i], NULL);
}

void		vm_server_thread_attr_destroy(pthread_attr_t *tattr)
{
	pthread_attr_destroy(tattr);
}

void		vm_server_mode_multithread(t_input *input)
{
	int		reg;

	reg = input->mode < 0 ? -input->mode : ONLINE;
	input->threads = malloc(sizeof(pthread_t) * reg);
	if (!(input->threads))
		vm_exit("Error: no multithread mode\n", input);
}
