/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:08:34 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int			vm_socket_block(int fd)
{
	int		flags;

	if ((flags = fcntl(fd, F_GETFL, NULL)) < 0)
		return (-1);
	if (fcntl(fd, F_SETFL, flags & ~O_NONBLOCK) < 0)
		return (-1);
	return (0);
}
