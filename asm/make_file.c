/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:51:57 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:51:59 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*make_filename(char *filename)
{
	char	*dot_cor;
	int		len;
	int		i;

	len = (int)ft_strlen(filename) - 1;
	i = 0;
	if (!(dot_cor = (char*)malloc(len + 4)))
	{
		ft_putstr_fd(ERROR_MEMORY_ALLOCATION,2);
		return (NULL);
	}
	while (i < len)
	{
		dot_cor[i] = filename[i];
		i++;
	}
	dot_cor[i++] = 'c';
	dot_cor[i++] = 'o';
	dot_cor[i++] = 'r';
	dot_cor[i++] = '\0';
	return (dot_cor);
}

int			make_file(t_data *data, char *filename)
{
	char	*dot_cor;

	if (!(dot_cor = make_filename(filename)))
		return (0);
	if ((data->fd = open(dot_cor, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
	{
		ft_putstr_fd("Can`t create file ", 2);
		ft_putstr_fd(dot_cor, 2);
		free(dot_cor);
		return (0);
	}
	write(data->fd, data->buffer, data->buffer_len);
	ft_putstr("Writing output program to ");
	ft_putstr(dot_cor);
	ft_putchar('\n');
	free(dot_cor);
	close(data->fd);
	return (1);
}
