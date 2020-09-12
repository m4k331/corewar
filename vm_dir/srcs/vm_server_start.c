/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_server_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:06:58 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:06:58 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static void			vm_init_fds_for_pull(t_input *input)
{
	input->fds[0].fd = 0;
	input->fds[0].events = POLLIN;
}

static void			vm_server_start_command_listener(t_input *input)
{
	if (input->mode == OFFLINE)
		return ;
	vm_socket_fill(&(input->io->hints));
	vm_socket_unblock(0);
	vm_socket_unblock(input->io->cout);
	vm_socket_unblock(input->io->sock_fd);
	vm_init_fds_for_pull(input);
	ft_printfd(input->io->cout, MSG_TO_CONNECT0);
	ft_printfd(input->io->cout, MSG_TO_CONNECT1);
	ft_printfd(input->io->cout, MSG_TO_CONNECT2);
}

void				vm_server_start(t_input *input)
{
	pthread_attr_t	tattr;

	vm_worker_manager_init(input);
	vm_server_start_command_listener(input);
	vm_server_mode_multithread(input);
	vm_server_thread_attr_set(&tattr, input->mode);
	vm_server_run(input, &tattr);
	vm_server_wait_for_threads(input, input->mode);
	vm_worker_manager_remove(input);
	vm_server_thread_attr_destroy(&tattr);
}
