/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_unblock.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:04:52 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
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
