/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:51:20 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:51:22 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		free_tmp_pointers(char *tmp, char *tmp_2)
{
	free(tmp);
	free(tmp_2);
}

void		epic_fight_with_norm(char *line, int *i)
{
	while (line[*i] && line[*i] != '\"')
		(*i)++;
}

int			get_continue_of_string(t_data *data, char *line)
{
	int		i;
	char	*tmp;
	char	*tmp_2;

	i = 0;
	epic_fight_with_norm(line, &i);
	if (line[i])
	{
		tmp = ft_strsub(line, 0, i + 1);
		tmp_2 = data->current_token->content;
		data->current_token->content = ft_strjoin(tmp_2, tmp);
		free_tmp_pointers(tmp, tmp_2);
		data->current_token->is_finished = 1;
		data->char_num = i + 1;
	}
	else
	{
		tmp = data->current_token->content;
		data->current_token->content = ft_strjoin(tmp, line);
		tmp_2 = data->current_token->content;
		data->current_token->content = ft_strjoin(tmp_2, "\n");
		free_tmp_pointers(tmp, tmp_2);
		data->char_num = i;
	}
	return (1);
}

int			memory_allocation_error(void)
{
	ft_putstr_fd(ERROR_MEMORY_ALLOCATION, 2);
	return (0);
}

int			is_string(t_data *data, char *line)
{
	int		i;
	char	*tmp;

	i = data->char_num + 1;
	while (line[i] && line[i] != '\"')
		i++;
	if (line[i] == '\"')
	{
		if (!init_token(data, line, STRING, i - data->char_num + 1))
			return (memory_allocation_error());
		data->char_num = i + 1;
	}
	else
	{
		if (!init_token(data, line, STRING, i - data->char_num))
			return (memory_allocation_error());
		tmp = data->current_token->content;
		data->current_token->content =
				ft_strjoin(data->current_token->content, "\n");
		free(tmp);
		data->current_token->is_finished = 0;
		data->char_num = i;
	}
	return (1);
}
