/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:02:42 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:02:42 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_io_interface.h"

void				vm_socket_fill(t_addrinfo *hints)
{
	ft_bzero(hints, sizeof(t_addrinfo));
	hints->ai_family = AF_UNSPEC;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = AI_PASSIVE;
}
