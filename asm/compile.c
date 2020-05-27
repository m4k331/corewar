/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:47:45 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:47:53 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				opening_failed(t_data *data, char *filename)
{
	ft_putstr_fd(ERROR_OPENING_FAILED, 2);
	ft_putstr_fd(filename, 2);
	ft_putchar_fd('\n', 2);
	close(data->fd);
	free_data(data);
	return (0);
}

int				free_and_return(t_data *data)
{
	free_data(data);
	return (0);
}

int				compile(char *filename)
{
	t_data		*data;

	if (!(data = init_data()))
		return (0);
	if ((data->fd = open(filename, O_RDONLY)) == -1)
		return (opening_failed(data, filename));
	if (!lexer(data, filename) || !check_last_end(data, filename))
	{
		close(data->fd);
		return (free_and_return(data));
	}
	close(data->fd);
	if (!make_tree(data))
		return (free_and_return(data));
	if (!parse_tree(data))
		return (free_and_return(data));
	calc_sizes(data);
	if (!make_hex_buffer(data))
		return (free_and_return(data));
	if (!make_file(data, filename))
		return (free_and_return(data));
	free_data(data);
	return (1);
}
