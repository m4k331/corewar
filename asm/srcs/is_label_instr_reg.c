/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_label_instr_reg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:50:28 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:50:30 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_label(t_data *data, char *line, int i)
{
	if (init_token(data, line, 10, i - data->char_num + 1))
	{
		data->char_num = i + 1;
		return (1);
	}
	return (0);
}

int		is_register(t_data *data, char *line, int i)
{
	if (init_token(data, line, 12, i - data->char_num))
	{
		data->char_num = i;
		return (1);
	}
	return (0);
}

int		is_instruction(t_data *data, char *line, int i)
{
	if (init_token(data, line, 11, i - data->char_num))
	{
		data->char_num = i;
		return (1);
	}
	return (0);
}

int		lex_error_label(t_data *data, int i)
{
	ft_putstr_fd(ERROR_LEXICAL, 2);
	ft_putchar_fd('[', 2);
	ft_putnbr_fd(data->line_num, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(i, 2);
	ft_putchar_fd(']', 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int		is_label_instr_reg(t_data *data, char *line)
{
	int	i;
	int	digit_counter;

	i = data->char_num + 1;
	digit_counter = 0;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
	{
		if (ft_isdigit(line[i]))
			digit_counter++;
		i++;
	}
	if (line[i] && line[i] == LABEL_CHAR)
		return (is_label(data, line, i));
	else if (!line[i] || line[i] == ' ' || line[i] == '\t'
				|| line[i] == SEPARATOR_CHAR
				|| line[i] == DIRECT_CHAR || line[i] == '-')
	{
		if (line[data->char_num] == 'r'
				&& ((i - data->char_num == 2 && digit_counter == 1)
				|| (i - data->char_num == 3 && digit_counter == 2)))
			return (is_register(data, line, i));
		return (is_instruction(data, line, i));
	}
	else
		return (lex_error_label(data, i));
}
