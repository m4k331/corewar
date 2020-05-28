/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:53:42 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:53:44 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_instruction_2(t_data *data)
{
	if (!ft_strcmp(data->current_token->content, "aff"))
		return (op_aff(data));
	else
	{
		error_instruction(data);
		return (0);
	}
}

int			check_instruction(t_data *data)
{
	if (!ft_strcmp(data->current_token->content, "live") ||
					!ft_strcmp(data->current_token->content, "zjmp") ||
					!ft_strcmp(data->current_token->content, "fork") ||
					!ft_strcmp(data->current_token->content, "lfork"))
		return (op_live_zjmp_fork_lfork(data));
	else if (!ft_strcmp(data->current_token->content, "ld") ||
					!ft_strcmp(data->current_token->content, "lld"))
		return (op_ld_lld(data));
	else if (!ft_strcmp(data->current_token->content, "st"))
		return (op_st(data));
	else if (!ft_strcmp(data->current_token->content, "add") ||
					!ft_strcmp(data->current_token->content, "sub"))
		return (op_add_sub(data));
	else if (!ft_strcmp(data->current_token->content, "and") ||
					!ft_strcmp(data->current_token->content, "or") ||
					!ft_strcmp(data->current_token->content, "xor"))
		return (op_and_or_xor(data));
	else if (!ft_strcmp(data->current_token->content, "ldi") ||
					!ft_strcmp(data->current_token->content, "lldi"))
		return (op_ldi_lldi(data));
	else if (!ft_strcmp(data->current_token->content, "sti"))
		return (op_sti(data));
	else
		return (check_instruction_2(data));
}

int			parse_tree(t_data *data)
{
	data->current_token = data->token;
	while (data->current_token->next)
	{
		if (!ft_strcmp(data->current_token->type, "INSTRUCTION"))
		{
			if (!check_instruction(data))
				return (0);
		}
		data->current_token = data->current_token->next;
	}
	return (1);
}
