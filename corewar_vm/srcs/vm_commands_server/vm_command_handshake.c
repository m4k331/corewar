/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_handshake.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:59:44 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:59:44 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int			vm_command_handshake_send(t_io_interface *io)
{
	uint8_t	msg[9];

	msg[0] = TYPE_HANDSHAKE;
	vm_socket_int_to_bytes(msg + 1, MAGIC_TOKEN, 4);
	vm_socket_int_to_bytes(msg + 5, ONLINE, 4);
	if ((9 != vm_socket_send(io->sock_fd, (void*)msg, 9)))
	{
		ft_putstr_fd(ERR_CANT_SEND_HANDSHAKE, io->err_fd);
		return (CODE_ERR_CANT_SEND_HANDSHAKE);
	}
	ft_printfd(io->cout, "Handshake to %s:%s sended\n", io->address, io->port);
	return (0);
}

int			vm_command_handshake_recv(t_io_interface *io)
{
	uint8_t	*msg;
	int		i;

	if (vm_socket_receive_data_wait(io, 5 + 4 * ONLINE) != 5 + 4 * ONLINE)
		return (vm_nofity_err(io->err_fd, ERR_SZ_HNDSHK, CD_ERR_SZ_HNDSHK));
	msg = (uint8_t*)io->netbuf->start;
	if (msg[0] != TYPE_HANDSHAKE)
		return (vm_nofity_err(io->err_fd, ERR_NOT_HNDSHK, CD_ERR_NOT_HNDSHK));
	if (vm_socket_bytes_to_int(msg + 1, 4) != MAGIC_TOKEN)
		return (vm_nofity_err(io->err_fd, ERR_HNDSHK_KEY, CD_ERR_HNDSHK_KEY));
	i = -1;
	while (++i < ONLINE)
		((t_input*)io->superior)->wk_sockets[i] =
		ft_itoa(vm_socket_bytes_to_int(msg + 5 + i * 4, 4));
	ft_printfd(io->cout, " from %s:%s received\n",
			io->address, io->port);
	darr_remove_front(io->netbuf, io->netbuf->len);
	return (0);
}
