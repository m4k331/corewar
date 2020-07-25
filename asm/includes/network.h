/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:24:18 by rnarbo            #+#    #+#             */
/*   Updated: 2020/07/01 00:08:07 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_H
# define NETWORK_H

# define THREADS				4
# define RECV_BUFF_SIZE			1024

# define MAX_CONNECTIONS		4
# define TCP_QUEUE_SIZE 		4

# define HUB_HEADER_SIZE		1
# define HANDSHAKE_MSG_LEN		5
# define ASM_MSG_HEADER_LEN		9

# define HANDSHAKE_MAGIC_OFFSET	1
# define ASM_MSG_LEN_OFFSET		5
# define ASM_BOT_ID_OFFSET		1

# define HUB_COMMAND_HANDSHAKE	101
# define HUB_COMMAND_SEND_BOT	3

# define ASM_COMMAND_HANDSHAKE	101
# define ASM_COMMAND_ERROR		102
# define ASM_COMMAND_BINARY		103

# define HANDSHAKE_MAGIC		0xFAF

# define THREAD_IN_USE			1
# define THREAD_FREE			0
# define THREAD_FINISHED		-1

# define DEFAULT_HUB_PORT		8008

# define USAGE_START "Usage: "
# define USAGE_ARGS	\
	" [-h] < -i hub_ip [-p hub_port] | champ_filename >\n"

typedef struct s_net_thread_param
{
	int		fd;
	char	thread_in_use;
	void	*data;
}	t_net_thread_param;

typedef struct s_hub_msg
{
	char	msg_type;
	void	*content;
}	t_hub_msg;

typedef struct s_asm_msg
{
	int bot_id;
	int len_msg;
	char *body;
}	t_asm_msg;

typedef struct s_thread_return
{
	int		error_code;
	char	*error_msg;
}	t_thread_return;

int	lexer_for_net(t_data *data, char *buff, size_t buff_size);
int	network(t_options *opt);

#endif