/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:53:31 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:53:33 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		free_token_and_content(t_token *token)
{
	if (token->type)
		free(token->type);
	if (token->content)
		free(token->content);
	free(token);
}

void		delete_token(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (tmp == data->current_token)
	{
		data->token = data->token->next;
		free_token_and_content(tmp);
		data->current_token = data->token;
	}
	else
	{
		while (tmp->next != data->current_token)
			tmp = tmp->next;
		tmp->next = data->current_token->next;
		free_token_and_content(data->current_token);
		data->current_token = tmp->next;
	}
}

int		parse_label(t_data *data)
{
	data->current_token = data->current_token->next;
	if (ft_strcmp(data->current_token->type, "INSTRUCTION") &&
			ft_strcmp(data->current_token->type, "ENDLINE") &&
			ft_strcmp(data->current_token->type, "COMMENT") &&
			ft_strcmp(data->current_token->type, "END"))
		return (error(data));
	return (1);
}

int			parse_token(t_data *data)
{
	if (!ft_strcmp(data->current_token->type, "ENDLINE") ||
			!ft_strcmp(data->current_token->type, "COMMENT"))
		delete_token(data);
	else if (!ft_strcmp(data->current_token->type, "LABEL"))
	{
		if (!parse_label(data))
			return (0);
	}
	else if (!ft_strcmp(data->current_token->type, "INSTRUCTION"))
	{
		if (!parse_instruction(data))
			return (0);
	}
	else
		return (error(data));
	return (1);
}
