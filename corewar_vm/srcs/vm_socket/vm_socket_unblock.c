/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_unblock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:03:07 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:03:07 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int			vm_socket_unblock(int fd)
{
	int		flags;

	if ((flags = fcntl(fd, F_GETFL, NULL)) < 0)
		return (-1);
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
		return (-1);
	return (0);
}
