/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_direct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:49:52 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:49:55 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_direct_label(t_data *data, char *line)
{
	int i;

	i = data->char_num + 2;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	if (init_token(data, line, 9, i - data->char_num))
	{
		data->char_num = i;
		return (1);
	}
	return (0);
}

int		is_direct_value(t_data *data, char *line)
{
	int	i;

	i = data->char_num + 1;
	if (line[i] == '-')
		i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (init_token(data, line, 8, i - data->char_num))
	{
		data->char_num = i;
		return (1);
	}
	return (0);
}

int		lex_error_direct(t_data *data)
{
	ft_putstr_fd(ERROR_LEXICAL, 2);
	ft_putchar_fd('[', 2);
	ft_putnbr_fd(data->line_num, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(data->char_num + 1, 2);
	ft_putchar_fd(']', 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int		is_direct(t_data *data, char *line)
{
	if (line[data->char_num + 1] && line[data->char_num + 1] == ':')
		return (is_direct_label(data, line));
	else if (line[data->char_num + 1] &&
				((line[data->char_num + 1] == '-'
				&& ft_isdigit(line[data->char_num + 2]))
				|| ft_isdigit(line[data->char_num + 1])))
		return (is_direct_value(data, line));
	return (lex_error_direct(data));
}
