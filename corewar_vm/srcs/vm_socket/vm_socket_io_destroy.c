/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_socket_io_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:05:53 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:05:56 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_io_interface.h"

void		vm_socket_io_destroy(t_io_interface *io)
{
	if (!io)
		return ;
	if (io->netbuf)
		darr_delete(io->netbuf);
	free(io);
}
