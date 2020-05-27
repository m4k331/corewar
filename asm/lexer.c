/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:51:33 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:51:35 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			get_tokens_from_line_2(t_data *data, char *line)
{
	if (line[data->char_num] == '.' && is_name_or_comment(data, line))
		return (1);
	else if (line[data->char_num] == '\"' && is_string(data, line))
		return (1);
	else if (line[data->char_num] == COMMENT_CHAR && is_comment(data, line))
		return (1);
	else if (line[data->char_num] == SEPARATOR_CHAR && is_separator(data, line))
		return (1);
	else if (line[data->char_num] == DIRECT_CHAR && is_direct(data, line))
		return (1);
	else if (line[data->char_num] == LABEL_CHAR && is_label_char(data, line))
		return (1);
	else if (((line[data->char_num] == '-'
			   && ft_isdigit(line[data->char_num + 1]))
			  || ft_isdigit(line[data->char_num]))
			 && is_num(data, line))
		return (1);
	else if (ft_strchr(LABEL_CHARS, line[data->char_num])
			 && is_label_instr_reg(data, line))
		return (1);
	return (0);
}

int			get_tokens_from_line(t_data *data, char *line)
{
	if (data->current_token && !line[0] && !data->current_token->is_finished)
		get_continue_of_string(data, "");
	while (line[data->char_num])
	{
		if (data->current_token && !data->current_token->is_finished)
			get_continue_of_string(data, line);
		else if (line[data->char_num] == ' ' || line[data->char_num] == '\t')
			data->char_num++;
		else if (get_tokens_from_line_2(data,line))
			continue ;
		else
			return (lex_error_label(data, data->char_num + 1));
	}
	if (line[0] && data->current_token && data->current_token->is_finished)
		init_token(data, line,  ENDLINE, 1);
	return (1);
}

int			gnl_error(char *filename)
{
	ft_putstr_fd(ERROR_READ_FILE, 2);
	ft_putstr_fd(filename, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int			empty_file(void)
{
	ft_putstr_fd("Champion`s file is empty.\n", 2);
	return (0);
}

int			lexer(t_data *data, char *filename)
{
	char	*line;
	int		gnl_result;
	int		i;

	i = 0;
	while ((gnl_result = get_next_line(data->fd, &line)))
	{
		i++;
		if (gnl_result == -1)
			return (gnl_error(filename));
		data->line_num++;
		data->char_num = 0;
		if (!get_tokens_from_line(data, line))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	free(line);
	if (i == 0)
		return (empty_file());
	data->line_num++;
	data->char_num = 0;
	return (1);
}
