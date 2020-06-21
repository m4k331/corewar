/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:48:50 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:48:52 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*g_name_of_type[] = {
	"ENDLINE",
	"NAME",
	"NAME_COMMENT",
	"STRING",
	"COMMENT",
	"SEPARATOR",
	"INDIRECT",
	"INDIRECT_LABEL",
	"DIRECT",
	"DIRECT_LABEL",
	"LABEL",
	"INSTRUCTION",
	"REGISTER",
	"END"
};

int			init_buffer(t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = data->current_byte + PROG_NAME_LENGTH + COMMENT_LENGTH + 17;
	if (!(data->buffer = (unsigned char*)malloc(len)))
	{
		ft_putstr_fd(ERROR_MEMORY_ALLOCATION, 2);
		return (0);
	}
	while (i < len)
		data->buffer[i++] = 0;
	data->buffer_len = len;
	return (1);
}

void		add_zeros(t_token *token)
{
	token->byte_number = 0;
	token->byte_size = 0;
	token->op_code = 0;
	token->args_size = 0;
	token->args_code = 0;
	token->t_dir_size = 0;
	token->args = NULL;
	token->next = NULL;
}

t_token		*init_token(t_data *data, char *line, int type, int len)
{
	t_token	*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
	{
		ft_putstr_fd(ERROR_MEMORY_ALLOCATION, 2);
		return (NULL);
	}
	token->char_num = data->char_num;
	token->line_num = data->line_num;
	token->type = ft_strdup(g_name_of_type[type]);
	token->content = ft_strsub(line, data->char_num, len);
	token->is_finished = 1;
	add_zeros(token);
	if (!data->current_token)
	{
		data->current_token = token;
		data->token = token;
	}
	else
	{
		data->current_token->next = token;
		data->current_token = token;
	}
	return (token);
}

t_data		*init_data(void)
{
	t_data	*data;

	if ((data = (t_data*)malloc(sizeof(t_data))) == NULL)
	{
		ft_putstr_fd(ERROR_MEMORY_ALLOCATION, 2);
		return (NULL);
	}
	data->fd = 0;
	data->line_num = 0;
	data->char_num = 0;
	data->buffer = NULL;
	data->buffer_len_iter = 0;
	data->current_byte = 0;
	data->buffer_len = 0;
	data->name = NULL;
	data->comment = NULL;
	data->current_token = NULL;
	data->token = NULL;
	return (data);
}
