/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op_weight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:48:37 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:48:40 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		if_indirect(t_data *data, t_token **arg, int arg_num)
{
	(*arg)->byte_number = data->current_byte;
	(*arg)->byte_size = 2;
	data->current_byte += 2;
	if (arg_num == 1 && data->current_token->args_code)
		data->current_token->args_code += 191;
	else if (arg_num == 2 && data->current_token->args_code)
		data->current_token->args_code += 48;
	else if (arg_num == 3 && data->current_token->args_code)
		data->current_token->args_code += 12;
	*arg = (*arg)->next;
}

void		if_direct(t_data *data, t_token **arg, int arg_num)
{
	(*arg)->byte_number = data->current_byte;
	(*arg)->byte_size = data->current_token->t_dir_size;
	data->current_byte += data->current_token->t_dir_size;
	if (arg_num == 1 && data->current_token->args_code)
		data->current_token->args_code += 127;
	else if (arg_num == 2 && data->current_token->args_code)
		data->current_token->args_code += 32;
	else if (arg_num == 3 && data->current_token->args_code)
		data->current_token->args_code += 8;
	*arg = (*arg)->next;
}

void		if_register(t_data *data, t_token **arg, int arg_num)
{
	(*arg)->byte_number = data->current_byte;
	(*arg)->byte_size = 1;
	data->current_byte += 1;
	if (arg_num == 1 && data->current_token->args_code)
		data->current_token->args_code += 63;
	else if (arg_num == 2 && data->current_token->args_code)
		data->current_token->args_code += 16;
	else if (arg_num == 3 && data->current_token->args_code)
		data->current_token->args_code += 4;
	*arg = (*arg)->next;
}

void		get_op_weight(t_data *data, unsigned char op_code,
							int t_dir_size, unsigned char args_code)
{
	t_token	*arg;
	int		arg_num;

	data->current_token->op_code = op_code;
	data->current_token->byte_number = data->current_byte;
	data->current_token->t_dir_size = t_dir_size;
	data->current_token->args_code = args_code;
	data->current_byte += 1;
	if (data->current_token->args_code)
		data->current_byte += 1;
	arg = data->current_token->args;
	arg_num = 0;
	while (arg)
	{
		if (arg->type[0] == 'D')
			if_direct(data, &arg, ++arg_num);
		else if (arg->type[0] == 'I')
			if_indirect(data, &arg, ++arg_num);
		else
			if_register(data, &arg, ++arg_num);
	}
	data->current_token->byte_size = data->current_byte
					- data->current_token->byte_number - 1;
	data->current_token = data->current_token->next;
}
