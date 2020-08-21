/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:47:45 by dorphan           #+#    #+#             */
/*   Updated: 2020/06/21 18:58:12 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

void			*opening_failed(t_data *data, char *filename)
{
	ft_putstr_fd(ERROR_OPENING_FAILED, 2);
	ft_putstr_fd(filename, 2);
	ft_putchar_fd('\n', 2);
	close(data->fd);
	free_data(data);
	return (NULL);
}

void			*free_and_return(t_data *data)
{
	free_data(data);
	return (NULL);
}

void			*work_with_file(t_data *data, char *filename)
{
	if ((data->fd = open(filename, O_RDONLY)) == -1)
		return (opening_failed(data, filename));
	if (!lexer(data, filename))
	{
		close(data->fd);
		return (free_and_return(data));
	}
	close(data->fd);
	if (!check_last_end(data, filename))
		return (free_and_return(data));
	return (filename);
}

// FIXME: надо наверно пофиксить ретурны при ошибках, но мне пока лень

/// Объясни, что не так, я поправлю. Сейчас на каждую ошибку есть соответствующий вывод.

// FIXME: Лучше наверно разбить на 2 части и в check_last_end происходит затирание открытого data->fd, надо пофиксить
// FIXED: Исправил затерание data->fd;
//			Разбил compile  на работу с файлом и работу с заполненной структурой data

#include <stdio.h> // не забыть убрать

t_data			*compile(char *filename)
{
	t_data		*data;

	if (!(data = init_data()))
		return (0);
	if (!work_with_file(data, filename))
		return (0);

    t_token *tmp = data->token;
    while (tmp) {
        printf("{%s}, [%s]\n", tmp->type, tmp->content);
        tmp = tmp->next;
    }
	if (!make_tree(data))
		return (free_and_return(data));
	if (!parse_tree(data))
		return (free_and_return(data));
	calc_sizes(data);
	if (!make_hex_buffer(data))
		return (free_and_return(data));
	// Убрал, чтобы можно было использовать функцию для сетевой части
	// if (!make_file(data, filename))
	// 	return (free_and_return(data));
	// free_data(data);
	return (data);
}
