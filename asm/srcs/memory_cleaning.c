/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:52:46 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:52:48 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			free_args(t_token *token)
{
	t_token		*tmp;
	t_token		*arg;

	arg = token->args;
	while (arg)
	{
		free(arg->type);
		free(arg->content);
		tmp = arg;
		arg = arg->next;
		free(tmp);
	}
}

void			free_name_and_comment(t_data *data)
{
	if (data->name)
	{
		if (data->name->type)
			free(data->name->type);
		if (data->name->content)
			free(data->name->content);
		free(data->name);
	}
	if (data->comment)
	{
		if (data->comment->type)
			free(data->comment->type);
		if (data->comment->content)
			free(data->comment->content);
		free(data->comment);
	}
}

void			free_data(t_data *data)
{
	t_token		*token;
	t_token		*tmp;

	token = data->token;
	while (token)
	{
		free(token->type);
		free(token->content);
		if (token->args)
			free_args(token);
		tmp = token;
		token = token->next;
		free(tmp);
	}
	free_name_and_comment(data);
	if (data->buffer)
		free(data->buffer);
	free(data);
}
