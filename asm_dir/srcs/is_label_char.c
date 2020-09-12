/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_label_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:50:09 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:50:12 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_lonely_label_char(t_data *data)
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

int		is_label_char(t_data *data, char *line)
{
	int	i;

	if (!line[data->char_num + 1]
			|| !ft_strchr(LABEL_CHARS, line[data->char_num + 1]))
		return (is_lonely_label_char(data));
	i = data->char_num + 1;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	if (init_token(data, line, 7, i - data->char_num))
	{
		data->char_num = i;
		return (1);
	}
	return (0);
}
