/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name_and_comment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:53:15 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:53:17 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_string_len(t_data *data, int t)
{
	int		len;

	len = (int)ft_strlen(data->current_token->content) - 2;
	if (t == 1 && len >= PROG_NAME_LENGTH)
	{
		ft_putstr_fd(ERROR_LONG_NAME, 2);
		return (0);
	}
	else if (t == 2 && len >= COMMENT_LENGTH)
	{
		ft_putstr_fd(ERROR_LONG_COMMENT, 2);
		return (0);
	}
	return (1);
}

void		remove_token(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!ft_strcmp(tmp->type, "NAME"))
		data->name = data->current_token;
	else if (!ft_strcmp(tmp->type, "NAME_COMMENT"))
		data->comment = data->current_token;
	data->current_token = data->token;
	delete_token(data);
	data->token = data->token->next;
	data->current_token = data->token;
}

int			check_string(t_data *data)
{
	if (!ft_strcmp(data->current_token->type, "NAME"))
	{
		data->current_token = data->current_token->next;
		if (ft_strcmp(data->current_token->type, "STRING"))
			return (error(data));
		else
		{
			if (!check_string_len(data, 1))
				return (0);
			remove_token(data);
		}
	}
	else
	{
		data->current_token = data->current_token->next;
		if (ft_strcmp(data->current_token->type, "STRING"))
			return (error(data));
		else
		{
			if (!check_string_len(data, 2))
				return (0);
			remove_token(data);
		}
	}
	return (1);
}

int			parse_name_and_comment(t_data *data, int calc)
{
	if (calc > 2)
		return (1);
	while (data->current_token->next
			&& (!ft_strcmp(data->current_token->type, "ENDLINE")
			|| !ft_strcmp(data->current_token->type, "COMMENT")))
		delete_token(data);
	if (!data->current_token->next)
		return (error(data));
	if (data->current_token->next
			&& (!ft_strcmp(data->current_token->type, "NAME")
			|| !ft_strcmp(data->current_token->type, "NAME_COMMENT")))
	{
		if (!check_string(data))
			return (0);
	}
	else
	{
		error(data);
		return (0);
	}
	return (parse_name_and_comment(data, ++calc));
}
