#include "asm.h"
#include "errors.h"

#include <stddef.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>

int create_socket(uint16_t port)
{
	int					listen_fd;
	struct sockaddr_in	addr;

	memset(&addr, 0, sizeof(addr));
	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Couldn't open listener socket");
		return (-1);
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	bind(socket, (struct sockaddr*)&addr, sizeof(addr));
	listen(socket, TCP_QUEUE_SIZE);
	return (listen_fd);
}

void compile_thread(void *param)
{
	int socket = (int)param;
	char *buffer;
	char *compilled;
	int	comp_len;

	buffer = get_buffer_from_socket(socket); // TODO: write get_buffer_from_socket()
	comp_len = compile(&compilled, buffer); // TODO: write compile()
	write_champion2socket(socket, compilled, comp_len); // TODO: write write_champion2socket()
	close(socket);
}

char *get_buffer_from_socket(int socket)
{
	int		recv_ret;
	char	*buffer;
	char	*tmp;
	char	recv_buff[BUFF_SIZE];
	size_t	buffer_size;

	buffer = NULL;
	buffer_size = 0;
	while ((recv_ret = recv(socket, recv_buff, BUFF_SIZE, 0)) > 0)
	{
		if ((tmp = (char *)realloc(buffer, buffer_size + recv_ret)) == 0)
		{
			free(buffer);
			return (0);
		}
		buffer = tmp;
		ft_memmove(buffer, recv_buff, recv_ret);
		buffer_size += recv_ret;
	}
	if (recv_ret < 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int network(t_options *opt)
{
	int					listen_fd;
	int					accepted_fd;
	pthread_t			comp_thread;

	if ((listen_fd = create_socket(opt->port)) < 0)
		return (-1);
	while (1)
	{
		if ((accepted_fd = accept(listen_fd, NULL, NULL)) < 0)
		{
			perror(ERR_ACCEPT);
			continue ;
		}
		if (pthread_create(&comp_thread, NULL, &compile_thread, (void *)accepted_fd) != 0)
		{
			perror(ERR_CREATE_THREAD);
			close(accepted_fd);
			continue ;
		}
	}
}