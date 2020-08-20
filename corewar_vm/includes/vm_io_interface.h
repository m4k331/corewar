/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_io_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:33:23 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:33:23 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_VM_IO_INTERFACE_H
# define VM_VM_IO_INTERFACE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <inttypes.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/wait.h>
# include <sys/poll.h>
# include <signal.h>
# include "libft.h"
# include "vm_messages.h"

# define MAGIC_TOKEN			0xC1C1
# define TYPE_HANDSHAKE			1
# define TYPE_GAME_COMING		2
# define TYPE_GAME_LOADED		3
# define TYPE_GAME_STAT			4
# define TYPE_OPERATION			5
# define TYPE_DEAD_PROC			6
# define TYPE_GAME_END			7
# define TYPE_CHAMP_PRES		8
# define TIMEOUT_CONNECT		5000
# define TIMEOUT_RECV			5000
# define MAXDATASIZE			1024 * 10
# define NETBUF_INITLEN			4096
# define ERROR_TOLERATE			5
# define SLEEPTIME 100000

typedef struct					s_message_header
{
	uint8_t						msg_type;
	uint32_t					game_id;
	uint32_t					msg_len;
}								t_message_header;

typedef struct					s_io_interface
{
	int							sock_fd;
	struct addrinfo				hints;
	char						*address;
	char						*port;
	char						*command;
	int							cout;
	int							err_fd;
	void						*superior;
	t_darr						*netbuf;
	int8_t						error_tolerate;
}								t_io_interface;

typedef struct sockaddr			t_sockaddr;
typedef struct addrinfo			t_addrinfo;

/*
** sockets part
*/

t_io_interface					*vm_socket_io_init(void *superior);
void							vm_socket_fill(struct addrinfo *hints);
int								vm_socket_connect(t_io_interface *io);
int								vm_socket_connect_wait(int sockfd,
								struct sockaddr *ai_addr, socklen_t ai_addrlen,
								int timeout);
void							vm_socket_io_clean(t_io_interface *io);
int								vm_socket_receive_data(t_io_interface *input,
								int32_t size_read_bytes);
int								vm_socket_receive_data_wait(t_io_interface *io,
								int32_t size_read_bytes);
int								vm_socket_block(int fd);
int								vm_socket_unblock(int fd);
int								vm_socket_close(int socket_fd,
								t_io_interface *input);
int								vm_socket_disconnect(t_io_interface *input);
int								vm_socket_send(int fd, void *data,
								int num_bytes);
int								vm_socket_send_buff(t_io_interface *io);
void							vm_socket_io_destroy(t_io_interface *io);
uint32_t						vm_socket_bytes_to_int(uint8_t *data_start,
								int32_t size);
void							vm_socket_int_to_bytes(uint8_t *data_start,
								int num, int32_t size);

#endif
