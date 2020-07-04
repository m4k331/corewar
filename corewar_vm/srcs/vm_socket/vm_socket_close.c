/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:08:21 by kona              #+#    #+#             */
/*   Updated: 2020/07/04 17:15:56 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int					vm_socket_close(int socketfd, t_io_interface *io)
{
	int				res;

	if (!(res = close(socketfd)))
		ft_printfd(io->cout, MSG_SOCK_SUCCESS_CLOSED,
				socketfd, io->address, io->port);
	else
		ft_printfd(io->err_fd, ERR_SOCK_CLOSED,
				socketfd, io->address, io->port);
	return (res);
}
