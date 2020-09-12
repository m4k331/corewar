/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_man_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:06:48 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:06:48 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_remove_all(t_input *g)
{
	if (g->worker_mngr)
		vm_worker_manager_remove(g);
	if (g->io)
		vm_socket_io_destroy(g->io);
	if (g->console_buffer)
		dstr_del(g->console_buffer);
	if (g->games_input_queue)
		darr_delete(g->games_input_queue);
	if (g->threads)
		free(g->threads);
}

void		vm_error(char *msg, t_input *g)
{
	if (msg)
	{
		if (g)
		{
			ft_putstr_fd(msg, g->io->err_fd);
			ft_putstr_fd("\n", g->io->err_fd);
		}
		else
		{
			ft_putstr_fd(msg, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	if (g)
		vm_remove_all(g);
	free(g);
	exit(1);
}

void		vm_exit(char *msg, t_input *g)
{
	if (msg)
	{
		if (g)
			ft_putstr_fd(msg, g->io->cout);
		else
			ft_putstr_fd(msg, 1);
	}
	if (g)
		vm_remove_all(g);
	free(g);
	exit(0);
}

int			vm_nofity_err(int fd, char *msg, int code)
{
	ft_putstr_fd(msg, fd);
	return (code ? code : 9999);
}
