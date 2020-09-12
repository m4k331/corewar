/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:53:05 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:53:06 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			is_arg(char *arg)
{
	if (!ft_strcmp(arg, "REGISTER") ||
		!ft_strcmp(arg, "DIRECT_LABEL") ||
		!ft_strcmp(arg, "DIRECT") ||
		!ft_strcmp(arg, "INDIRECT_LABEL") ||
		!ft_strcmp(arg, "INDIRECT"))
		return (1);
	return (0);
}

int			addition_1(t_data *data)
{
	data->current_token = data->current_token->next;
	return (error(data));
}

void		addition_2(t_data *data, t_token *arg)
{
	t_token	*tmp;

	tmp = data->current_token->args;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = arg;
}

int			addition_3(t_data *data)
{
	t_token	*tmp;

	tmp = data->current_token;
	data->current_token = data->current_token->next;
	delete_token(data);
	data->current_token = tmp;
	return (parse_instruction(data));
}

int			parse_instruction(t_data *data)
{
	t_token	*arg;

	arg = data->current_token->next;
	if (data->current_token->args && !ft_strcmp(arg->type, "ENDLINE"))
	{
		data->current_token = data->current_token->next;
		return (1);
	}
	if (!is_arg(arg->type))
		return (addition_1(data));
	if (!data->current_token->args)
		data->current_token->args = arg;
	else
		addition_2(data, arg);
	data->current_token->next = arg->next;
	arg->next = NULL;
	if (!ft_strcmp(data->current_token->next->type, "SEPARATOR")
			&& is_arg(data->current_token->next->next->type))
		return (addition_3(data));
	else if (!ft_strcmp(data->current_token->next->type, "ENDLINE"))
		return (parse_instruction(data));
	data->current_token = data->current_token->next;
	return (error(data));
}
