/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_sizes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:46:54 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:47:00 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		put_operation_weight_2(t_data *data)
{
	if (!ft_strcmp(data->current_token->content, "sti"))
		get_op_weight(data, 0x0b, 2, 1);
	else if (!ft_strcmp(data->current_token->content, "fork"))
		get_op_weight(data, 0x0c, 2, 0);
	else if (!ft_strcmp(data->current_token->content, "lld"))
		get_op_weight(data, 0x0d, 4, 1);
	else if (!ft_strcmp(data->current_token->content, "lldi"))
		get_op_weight(data, 0x0e, 2, 1);
	else if (!ft_strcmp(data->current_token->content, "lfork"))
		get_op_weight(data, 0x0f, 2, 0);
	else if (!ft_strcmp(data->current_token->content, "aff"))
		get_op_weight(data, 0x10, 4, 1);
}

void		put_operation_weight(t_data *data)
{
	if (!ft_strcmp(data->current_token->content, "live"))
		get_op_weight(data, 0x01, 4, 0);
	else if (!ft_strcmp(data->current_token->content, "ld"))
		get_op_weight(data, 0x02, 4, 1);
	else if (!ft_strcmp(data->current_token->content, "st"))
		get_op_weight(data, 0x03, 4, 1);
	else if (!ft_strcmp(data->current_token->content, "add"))
		get_op_weight(data, 0x04, 4, 1);
	else if (!ft_strcmp(data->current_token->content, "sub"))
		get_op_weight(data, 0x05, 4, 1);
	else if (!ft_strcmp(data->current_token->content, "and"))
		get_op_weight(data, 0x06, 4, 1);
	else if (!ft_strcmp(data->current_token->content, "or"))
		get_op_weight(data, 0x07, 4, 1);
	else if (!ft_strcmp(data->current_token->content, "xor"))
		get_op_weight(data, 0x08, 4, 1);
	else if (!ft_strcmp(data->current_token->content, "zjmp"))
		get_op_weight(data, 0x09, 2, 0);
	else if (!ft_strcmp(data->current_token->content, "ldi"))
		get_op_weight(data, 0x0a, 2, 1);
	else
		put_operation_weight_2(data);
}

void		calc_sizes(t_data *data)
{
	data->current_token = data->token;
	while (data->current_token->next)
	{
		if (!ft_strcmp(data->current_token->type, "LABEL"))
			data->current_token = data->current_token->next;
		else
		{
			data->current_token->byte_number = data->current_byte;
			data->current_token->byte_size = 1;
			put_operation_weight(data);
		}
	}
}
