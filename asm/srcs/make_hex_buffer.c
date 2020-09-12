/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_hex_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:52:06 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:52:09 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				put_magic(t_data *data, int *current_pos)
{
	data->buffer[(*current_pos)++] = (char)0x00;
	data->buffer[(*current_pos)++] = (char)0xea;
	data->buffer[(*current_pos)++] = (char)0x83;
	data->buffer[(*current_pos)++] = (char)0xf3;
}

void				put_name(t_data *data, int *current_pos)
{
	int				i;
	int				c;

	i = 1;
	c = *current_pos;
	while (data->name->content[i] != '\"')
		data->buffer[(*current_pos)++] = data->name->content[i++];
	*current_pos = c + PROG_NAME_LENGTH + 4;
}

void				put_comment(t_data *data, int *current_pos)
{
	int				i;
	int				c;

	i = 1;
	c = *current_pos;
	while (data->comment->content[i] != '\"')
		data->buffer[(*current_pos)++] = data->comment->content[i++];
	*current_pos = c + COMMENT_LENGTH + 4;
}

void				put_code_size(t_data *data, int *current_pos)
{
	unsigned char	*byte;
	int				i;

	byte = ((unsigned char*)&(data->current_byte)) + 3;
	i = 0;
	while (i++ < 4)
		data->buffer[(*current_pos)++] = *byte--;
}

int					make_hex_buffer(t_data *data)
{
	int				current_pos;

	current_pos = 0;
	if (!init_buffer(data))
		return (0);
	put_magic(data, &current_pos);
	put_name(data, &current_pos);
	put_code_size(data, &current_pos);
	put_comment(data, &current_pos);
	if (!put_commands(data, &current_pos))
		return (0);
	return (1);
}
