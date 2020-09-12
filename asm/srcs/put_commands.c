/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:53:55 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:53:57 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					put_num(t_data *data, t_token *arg,
							int *current_pos, long content)
{
	char			sign;
	unsigned char	*byte;
	int				i;

	sign = 0;
	i = arg->byte_size - 1;
	if (content < 0)
	{
		content *= -1;
		sign = 1;
	}
	content = (sign) ? ~content + 1 : content;
	byte = ((unsigned char*)&content) + i;
	while (i-- >= 0)
		data->buffer[(*current_pos)++] = *byte--;
	return (1);
}

int					put_label(t_data *data, t_token *arg,
								int *current_pos, char *c)
{
	t_token			*tmp;
	int				len;
	long			content;

	tmp = data->token;
	len = ft_strlen(c);
	while (tmp && (ft_strncmp(tmp->content, c, len)
			|| (!ft_strncmp(tmp->content, c, len)
			&& tmp->content[len] != LABEL_CHAR)))
		tmp = tmp->next;
	if (!tmp)
		return (error_no_label(data, arg, c));
	else
	{
		while (tmp && !ft_strcmp(tmp->type, "LABEL"))
			tmp = tmp->next;
		if (!tmp)
			content = data->current_token->byte_size;
		else
			content = tmp->byte_number - data->current_token->byte_number;
		return (put_num(data, arg, current_pos, content));
	}
}

int					put_arg(t_data *data, t_token *arg, int *current_pos)
{
	long			content;
	char			*c;

	c = arg->content;
	if (*c == 'r' || *c == '%')
		c++;
	if (*c == ':')
		return (put_label(data, arg, current_pos, ++c));
	content = ft_atoli(c);
	return (put_num(data, arg, current_pos, content));
}

int					put_commands(t_data *data, int *current_pos)
{
	t_token			*arg;

	data->current_token = data->token;
	while (data->current_token->next)
	{
		if (data->current_token->type[0] != 'L')
		{
			data->buffer[(*current_pos)++] = data->current_token->op_code;
			if (data->current_token->args_code)
				data->buffer[(*current_pos)++] = data->current_token->args_code;
			arg = data->current_token->args;
			while (arg)
			{
				if (!put_arg(data, arg, current_pos))
					return (0);
				arg = arg->next;
			}
		}
		data->current_token = data->current_token->next;
	}
	return (1);
}
