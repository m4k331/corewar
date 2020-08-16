/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:35:31 by rnarbo            #+#    #+#             */
/*   Updated: 2020/08/16 15:48:29 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "network.h"
#include "errors.h"

#include <stddef.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <pthread.h>

// Delete
#include <stdio.h>
#include <arpa/inet.h>


// int create_socket(uint16_t port)
// {
// 	int					listen_fd;
// 	struct sockaddr_in	addr;

// 	memset(&addr, 0, sizeof(addr));
// 	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
// 	{
// 		perror("Couldn't open listener socket");
// 		return (-1);
// 	}
// 	addr.sin_family = AF_INET;
// 	addr.sin_addr.s_addr = htonl(INADDR_ANY);
// 	addr.sin_port = htons(port);

// 	bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
// 	listen(listen_fd, TCP_QUEUE_SIZE);
// 	return (listen_fd);
// }

int free_msg(t_hub_msg *msg);
int send_msg(int fd, t_hub_msg *msg);

int print_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	return (-1);
}

t_hub_msg *create_error_struct(int bot_id, char *err_msg)
{
	t_hub_msg *ret;

	if ((ret = (t_hub_msg *)malloc(sizeof(t_hub_msg))) == NULL)
		return NULL;
	ret->msg_type = ASM_COMMAND_ERROR;
	if ((ret->content = (t_asm_msg *)malloc(sizeof(t_asm_msg))) == NULL)
	{
		free_msg(ret);
		return (NULL);
	}
	((t_asm_msg *)ret->content)->bot_id = bot_id;
	((t_asm_msg *)ret->content)->len_msg = ft_strlen(err_msg);
	((t_asm_msg *)ret->content)->body = ft_strdup(err_msg);
	return (ret);
}

int send_error_msg(int fd, int bot_id, char *err_msg)
{
	t_hub_msg *err;

	if ((err = create_error_struct(bot_id, err_msg)) == NULL)
		return -1;
	if (send_msg(fd, err) < 0)
		return (-1 | free_msg(err));
	free_msg(err);
	return (0);
}

// void set_thread_dead(void *param)
// {
// 	printf("cleanup\n");
// 	((t_net_thread_param *)param)->thread_in_use = THREAD_FINISHED;
// 	printf("here is ok\n");
// 	printf("%p -> %p\n", ((t_net_thread_param *)param)->data, ((t_hub_msg *)((t_net_thread_param *)param)->data)->content);
// 	// ((t_asm_msg *)((t_hub_msg *)((t_net_thread_param *)param)->data)->content)->body;
// 	// free_msg(((t_net_thread_param *)param)->data);
// 	printf("freed\n");
// 	printf("freed\n");
// 	printf("freed\n");
// }

void *set_thread_dead(void *param)
{
	((t_net_thread_param *)param)->thread_in_use = THREAD_FINISHED;
	free_msg(((t_net_thread_param *)param)->data);
	return NULL;
}

void *asm_thread(void *param) //FIXME: free()
{
	int		fd;
	t_data	*data;
	t_asm_msg *amsg;

	fd = ((t_net_thread_param *)param)->fd;
	amsg = ((t_hub_msg *)((t_net_thread_param *)param)->data)->content;
	if ((data = init_data()) == NULL)
	{
		free_data(data);
		send_error_msg(fd, amsg->bot_id, "Error while init_data!");
		return (set_thread_dead(param));
	}
	// write(2, amsg->body, amsg->len_msg);
	if (amsg->body[amsg->len_msg - 1] != '\n')
	{
		free_data(data);
		send_error_msg(fd, amsg->bot_id, "Error bot has no endline at the end!");
		return (set_thread_dead(param));
	}
	if (!lexer_for_net(data, amsg->body, amsg->len_msg))
	{
		free_data(data);
		send_error_msg(fd, amsg->bot_id, "Error while lexing!");
		return (set_thread_dead(param));
	}
	init_token(data, "(null)", 13, 6);
	if (!make_tree(data))
	{
		free_data(data);
		send_error_msg(fd, amsg->bot_id, "Error while making tree!");
		return (set_thread_dead(param));
	}
	if (!parse_tree(data))
	{
		free_data(data);
		send_error_msg(fd, amsg->bot_id, "Error while parsing tree!");
		return (set_thread_dead(param));
	}
	calc_sizes(data);
	if (!make_hex_buffer(data))
	{
		free_data(data);
		send_error_msg(fd, amsg->bot_id, "Error while creating hex buffer!");
		return (set_thread_dead(param));
	}
	free(amsg->body);
	amsg->len_msg = data->buffer_len - 1;
	if ((amsg->body = (char *)malloc(amsg->len_msg)) == NULL)
	{
		free_data(data);
		send_error_msg(fd, amsg->bot_id, "Error while allocating msg!");
		return (set_thread_dead(param));
	}
	ft_memmove(amsg->body, data->buffer, amsg->len_msg);
	free_data(data);
	((t_hub_msg *)((t_net_thread_param *)param)->data)->msg_type = ASM_COMMAND_BINARY;
	send_msg(fd, ((t_net_thread_param *)param)->data);
	return set_thread_dead(param);
}

int set_keep_alive(int fd)
{
	int		on;
	int		flags;

	on = 1;
	flags = 10;
	if (setsockopt(fd, SOL_SOCKET,  SO_KEEPALIVE, &on, sizeof on) < 0)
		return (-1); // TODO: обработка ошибки
	if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPALIVE, &flags, sizeof flags) < 0)
		return (-1); // TODO: обработка ошибки
	// flags = 5;
	// if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &flags, sizeof(flags))) // TODO: check
	// 	return (-1); // TODO: обработка ошибок
	// flags = 5;
	// if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &flags, sizeof(flags))) // TODO: check
	// 	return (-1); // TODO: обработка ошибок
	return (0);
}

// TODO: дописать обработку ошибок
int create_keep_alive_socket(char *ip, short port)
{
	int					fd;
	struct sockaddr_in	addr;

	if ((fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		return (-1);
	ft_memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip, &addr.sin_addr) < 0)
		return (-1 | close(fd));
	if (set_keep_alive(fd) < 0)
		return (-1 | close(fd));
	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		return (-1 | close(fd));
	return (fd);
}

int recv_needed(char *msg, ssize_t msg_len)
{
	printf("test recv needed\n");
	if (msg_len == 0)
		return (1);
	if (*msg == HUB_COMMAND_HANDSHAKE)
	{
		if (msg_len < HANDSHAKE_MSG_LEN)
			return (1);
	}
	else if (*msg == HUB_COMMAND_SEND_BOT)
	{
		if (msg_len < ASM_MSG_LEN_OFFSET)
			return (1);
		printf("data_len: %d\n", htonl(*(uint32_t *)(msg + ASM_MSG_LEN_OFFSET)));
		if (msg_len < ASM_MSG_HEADER_LEN + htonl(*(uint32_t *)(msg + ASM_MSG_LEN_OFFSET)))
			return (1);
	}
	return (0);
}

int free_msg(t_hub_msg *msg)
{
	if (msg == NULL)
		return (0);
	if (msg->msg_type == HUB_COMMAND_SEND_BOT ||
		msg->msg_type == ASM_COMMAND_BINARY ||
		msg->msg_type == ASM_COMMAND_ERROR)
		if (msg->content != NULL)
			free(((t_asm_msg *)msg->content)->body);
	free(msg->content);
	free(msg);
	return (0);
}

int create_asm_msg_struct(t_asm_msg **asm_msg, uint32_t bot_id, char *body, ssize_t body_size)
{
	if ((*asm_msg = (t_asm_msg *)malloc(sizeof(t_asm_msg))) == NULL)
		return (-1);
	(*asm_msg)->len_msg = body_size;
	(*asm_msg)->bot_id = bot_id;
	if (((*asm_msg)->body = (char *)malloc((*asm_msg)->len_msg)) < 0)
		return (-1);
	ft_memmove((*asm_msg)->body, body, (*asm_msg)->len_msg);
	return (0);
}

int parse_hub_msg_struct(t_hub_msg **msg, char *buff, ssize_t buff_len)
{
	if (buff_len == 0)
		return (-2);
	if ((*msg = (t_hub_msg *)malloc(sizeof(t_hub_msg))) == NULL)
		return (-1);
	printf("Line: %d\n", __LINE__);
	ft_memset(*msg, 0, sizeof(t_hub_msg));
	printf("Line: %d\n", __LINE__);
	(*msg)->msg_type = *buff;
	printf("Line: %d\n", __LINE__);
	printf("msg type: %hhd\n", (*msg)->msg_type);
	if ((*msg)->msg_type == HUB_COMMAND_HANDSHAKE)
	{
		printf("Line: %d\n", __LINE__);
		if (buff_len != HANDSHAKE_MSG_LEN)
			return (-2 | free_msg(*msg));
		printf("Line: %d\n", __LINE__);
		if (((*msg)->content = malloc(sizeof(uint32_t))) == NULL)
			return (-1 | free_msg(*msg));
		printf("Line: %d\n", __LINE__);
		*((uint32_t *)(*msg)->content) = htonl(*(uint32_t *)(buff + HANDSHAKE_MAGIC_OFFSET));
		printf("Line: %d\n", __LINE__);
		if (*((uint32_t *)(*msg)->content) != HANDSHAKE_MAGIC)
			return (-1 | free_msg(*msg));
		printf("Line: %d\n", __LINE__);
	}
	else if ((*msg)->msg_type == HUB_COMMAND_SEND_BOT)
	{
		printf("Line: %d\n", __LINE__);
		printf("Full len: %u\n", htonl(*(uint32_t *)(buff + ASM_MSG_LEN_OFFSET)));
		if (buff_len < ASM_MSG_HEADER_LEN ||
			buff_len != ASM_MSG_HEADER_LEN + htonl(*(uint32_t *)(buff + ASM_MSG_LEN_OFFSET)))
			return (-2 | free_msg(*msg));
		printf("Line: %d\n", __LINE__);
		if (create_asm_msg_struct((t_asm_msg **)&((*msg)->content),
				htonl(*(uint32_t *)(buff + ASM_BOT_ID_OFFSET)),
				buff + ASM_BODY_OFFSET,
				htonl(*(uint32_t *)(buff + ASM_MSG_LEN_OFFSET))) < 0)
			return (-1 | free_msg(*msg));
		printf("Line: %d\n", __LINE__);
		// if (((*msg)->content = malloc(sizeof(t_asm_msg))) == NULL)
		// 	return (-1 | free_msg(msg));
		// ((t_asm_msg *)(*msg)->content)->len_msg = *(uint32_t *)(buff + ASM_MSG_LEN_OFFSET);
		// ((t_asm_msg *)(*msg)->content)->bot_id = *(uint32_t *)(buff + ASM_BOT_ID_OFFSET);
		// if ((((t_asm_msg *)(*msg)->content)->body = (char *)malloc((t_asm_msg *)(*msg)->content)->len_msg) < 0)
		// 	return (-1 | free_msg(msg));
		// ft_memmove((t_asm_msg *)(*msg)->content)->body, buff + ASM_MSG_HEADER_LEN, (t_asm_msg *)(*msg)->content)->len_msg);
	}
	else
		return (-1);
	return (0);
}

int recv_command(t_hub_msg **msg, int fd)
{
	void	*buff;
	void	*tmp;
	ssize_t	buff_len;
	ssize_t	recv_len;
	char	recv_buff[RECV_BUFF_SIZE];

	buff_len = 0;
	buff = NULL;
	printf("recv_command\n");
	while (recv_needed(buff, buff_len))
	{
		recv_len = recv(fd, recv_buff, RECV_BUFF_SIZE, 0);
		if (recv_len <= 0)
		{
			free(buff);
			return (recv_len ? -1 : 1);
		}
		if ((tmp = realloc(buff, buff_len + recv_len)) == NULL)
		{
			free(buff);
			return (-1);
		}
		buff = tmp;
		ft_memmove(buff + buff_len, recv_buff, recv_len);
		buff_len += recv_len;
//		printf("Recieved: %zd\n", buff_len);
	}
	write(1, "\'", 1);
	write(1, buff, buff_len);
	write(1, "\'\n", 2);
	printf("parse_hub_msg\n");
	if (parse_hub_msg_struct(msg, buff, buff_len) < 0)
	{
		free(buff);
		send_error_msg(fd, -1, "Error: invalid msg!");
		return (-1); // FIXME: 
	}
	printf("OK!\n");
	free(buff);
	return (0);
}

int find_unused_thread(t_net_thread_param *threads_data, int threads_num)
{
	int i;

	i = 0;
	printf("Finding unused thread\n");
	while (i < threads_num)
	{
		if (threads_data[i].thread_in_use == THREAD_FREE)
			return (i);
		i++;
	}
	return (-1);
}

int send_msg(int fd, t_hub_msg *msg)
{
	char *buff;
	int buff_len;
	int ret_val;

	if (msg->msg_type == HUB_COMMAND_HANDSHAKE ||
		msg->msg_type == ASM_COMMAND_HANDSHAKE)
	{
		buff_len = HANDSHAKE_MSG_LEN;
		if ((buff = (char *)malloc(buff_len)) == NULL)
			return (-1);
		*(uint32_t *)(buff + 1) = htonl(*(uint32_t *)msg->content);
	}
	if (msg->msg_type == HUB_COMMAND_SEND_BOT ||
		msg->msg_type == ASM_COMMAND_BINARY ||
		msg->msg_type == ASM_COMMAND_ERROR)
	{
		buff_len = ASM_MSG_HEADER_LEN + ((t_asm_msg *)msg->content)->len_msg;
		if ((buff = (char *)malloc(buff_len)) == NULL)
			return (-1);
		*(uint32_t *)(buff + ASM_BOT_ID_OFFSET) = htonl(((t_asm_msg *)msg->content)->bot_id);
		*(uint32_t *)(buff + ASM_MSG_LEN_OFFSET) = htonl(((t_asm_msg *)msg->content)->len_msg);
		printf("msg_len: %d\n", htonl(((t_asm_msg *)msg->content)->len_msg));
		ft_memmove(buff + ASM_MSG_HEADER_LEN, ((t_asm_msg *)msg->content)->body, ((t_asm_msg *)msg->content)->len_msg);
	}
	buff[0] = msg->msg_type;
	ret_val = send(fd, buff, buff_len, 0);
	free(buff);
	return (ret_val < 0 ? -1 : 0);
}

int handle_finished_threads(pthread_t *threads_pool, t_net_thread_param *threads_data, int threads_cnt)
{
	int		i;
	void	*thread_return;

	i = 0;
	printf("Handling finihed thread\n");
	while (i < threads_cnt)
	{
		if (threads_data[i].thread_in_use == THREAD_FINISHED)
		{
			if (pthread_join(threads_pool[i], &thread_return) != 0)
				;// TODO: обработка ошибки
			// TODO: обработка результатов
			threads_data[i].thread_in_use = THREAD_FREE;
		}
		i++;
	}
	return (0);
}

int wait_threads_finish(pthread_t *threads_pool, t_net_thread_param *threads_data, int threads_cnt)
{
	int i;
	void *thread_return;

	i = 0;
	while (i < threads_cnt)
	{
		if (threads_data[i].thread_in_use != THREAD_FREE)
		{
			if (pthread_join(threads_pool[i], &thread_return) != 0)
				;// TODO: обработка ошибки
			// TODO: обработка результатов
			threads_data[i].thread_in_use = THREAD_FREE;
		}
		i++;
	}
	return (0);
}

int create_handshake_msg(t_hub_msg **msg)
{
	if ((*msg = (t_hub_msg *)calloc(sizeof(t_hub_msg), 1)) == NULL)
		return (-1);
	(*msg)->msg_type = ASM_COMMAND_HANDSHAKE;
	if (((*msg)->content = calloc(sizeof(uint32_t), 1)) == 0)
		return (-1 | free_msg(*msg));
	*((uint32_t *)(*msg)->content) = HANDSHAKE_MAGIC;
	return (0);
}

int handshake(int fd)
{
	t_hub_msg	*msg;

	printf("Creating handshake msg\n");
	if (create_handshake_msg(&msg) < 0)
		return (-1); // TODO: error handle
	printf("Sending handshake msg\n");
	if (send_msg(fd, msg) < 0)
		return (-1 | free_msg(msg));
	free_msg(msg);
	printf("Recieving handshake\n");
	if (recv_command(&msg, fd) < 0)
		return (-1);
	printf("Recieved handshake\n");
	if (msg->msg_type != HUB_COMMAND_HANDSHAKE)
		return (-1 | free_msg(msg));
	free_msg(msg);
	return (0);
}

int network(t_options *opt)
{
	int					fd;
	pthread_t			threads_pool[THREADS];
	t_net_thread_param	thread_data[THREADS];
	t_hub_msg			*msg;
	int					thread;
	int					recv_ret;

	if ((fd = create_keep_alive_socket(opt->ip, opt->port)) < 0)
		return (-1);
	if (handshake(fd) < 0)
		return (-1); // TODO: handle
	ft_memset(thread_data, 0, sizeof(thread_data));
	printf("Main while starts\n");
	while (1)
	{
		if (handle_finished_threads(threads_pool, thread_data, THREADS) < 0)
			break ;
		if ((thread = find_unused_thread(thread_data, THREADS)) < 0)
			continue ;
		printf("Unused thread found\n");
		if ((recv_ret = recv_command(&msg, fd)) < 0) // FIXME: обработка ошибок
			continue ;
		if (recv_ret == 1)
			break;
		printf("Command received\n");
		if (msg->msg_type == HUB_COMMAND_HANDSHAKE)
			free_msg(msg);
		if (msg->msg_type == HUB_COMMAND_SEND_BOT)
		{
			thread_data[thread].fd = fd;
			thread_data[thread].data = msg;
			thread_data[thread].thread_in_use = 1;
			printf("Creating thread\n");
			if (pthread_create(threads_pool + thread, NULL, &asm_thread, thread_data + thread) != 0)
			{
				free_msg(thread_data[thread].data);
				break ;
			}
			// asm_thread(thread_data + thread);
			// exit(0);
			printf("Thread created\n");
		}
	}
	printf("While ended, waiting for threads finish\n");
	if (wait_threads_finish(threads_pool, thread_data, THREADS) < 0)
		return (-1 | close(fd));
	printf("Threads finished\n");
	return (0 | close(fd));
}

size_t ft_linelen(char *line, size_t max_len)
{
	size_t i;

	i = 0;
	while (line[i] && line[i] != '\n' && i < max_len)
		i++;
	return (i);
}

int get_line_from_buffer(char **line, char *buff, size_t buff_len, int line_n)
{
	int		line_len;
	size_t	j;
	int		i;

	if (!buff)
		return (-1);
	i = 0;
	j = 0;
	while (i < line_n && j < buff_len)
	{
		if (buff[j] == '\n' || buff[j] == '\0')
			i++;
		j++;
	}
	*line = NULL;
	if (j == buff_len)
		return (0);
	line_len = ft_linelen(buff + j, buff_len - j);
	if ((*line = (char *)malloc(line_len +
		((line_len + j == buff_len) ? 1 : 0))) == NULL)
		return (-1);
	ft_memmove(*line, buff + j, line_len);
	(*line)[line_len - ((line_len + j == buff_len) ? -1 : 0)] = '\0';
	return (1);
}

// TODO: перенести в хедер
int			empty_file(void);
int			gnl_error(char *);
int			get_tokens_from_line(t_data *data, char *line);

int			lexer_for_net(t_data *data, char *buff, size_t buff_size)
{
	// char	*line;
    char	*delim;
	// int		gnl_result;
	int		i;
	int     ln;
	char   *newline;

	i = 0;
	while (buff_size > 0)
	{
		delim = memchr(buff, '\n', buff_size);
		if (delim == NULL) {
			delim = buff + buff_size;
		}
		ln = delim - buff + 1;
		if ((newline = (char *)malloc(ln)) == NULL)
			return (0);
		ft_memset(newline, 0, ln);
		memcpy(newline, buff, ln-1);
		buff = delim + 1;
		buff_size -= ln;
		printf("LINE_FROM_BUFFER: <%s>\n", newline);
		i++;
		data->line_num++;
		data->char_num = 0;

		if (!get_tokens_from_line(data, newline))
		{
			free(newline);
			return (0);
		}
		free(newline);
	}
	printf("%d\n", __LINE__);
//	free(line);
	if (i == 0)
		return (empty_file());
	printf("%d\n", __LINE__);
	data->line_num++;
	data->char_num = 0;
	printf("%d\n", __LINE__);
	return (1);
}
