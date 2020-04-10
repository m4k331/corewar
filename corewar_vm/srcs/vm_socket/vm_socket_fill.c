/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:06:20 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:06:20 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_io_interface.h"

void				vm_socket_fill(struct addrinfo *hints)
{
	ft_bzero(hints, sizeof(struct addrinfo));
	hints->ai_family = AF_UNSPEC;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = AI_PASSIVE;
}
