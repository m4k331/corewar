/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 00:43:00 by rnarbo            #+#    #+#             */
/*   Updated: 2020/04/03 02:36:53 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

#include <stddef.h>

t_token_type	classify_token(t_token_type *type, char *token)
{

}

int				set_token_sep(t_token *token, char *str)
{
	token = malloc(sizeof(t_token));
	token->content = malloc(sizeof(char));
	*(char *)token->content = *str;
	token->next = NULL;
	token->type = SEP;
}

int				set_token_op(t_token *token, char *str);
int				set_token_comment(t_token *token, char *str);
int				set_token_str(t_token *token, char *str);
int				set_token_cmd(t_token *token, char *str);
int				set_token_lblu(t_token *token, char *str);
int				set_token_lbli(t_token *token, char *str);
int				set_token_reg(t_token *token, char *str);
int				set_token_num(t_token *token, char *str);

int				set_token(t_token *token, char *str)
{
	if (*str == COMMAND_CHAR)
		return (set_token_cmd(token, str));
	else if (*str == COMMENT_CHAR)
		return (set_token_comment(token, str));
	else if (*str == STR_CHAR)
		return (set_token_str(token, str));
	else if (*str == DIRECT_CHAR || *str == NL_CHAR || *str == SEPARATOR_CHAR)
		return (set_token_sep(token, str));
	else if (*str == LABEL_CHAR)
		return (set_token_lblu(token, str));
	else if (is_label(str))
		return (set_token_lbli(token, str));
	else if (is_register(str))
		return (set_token_reg(token, str));
	else if (ft_isdigit(*str))
		return (set_token_num(token, str));
	else
		return (set_token_op(token, str));
}

t_token_stream	*scanner(char *buffer)
{
	t_token_stream	*stream;
	int				i;
	int				token_len;

	if ((stream = (t_token_stream *)malloc(sizeof(t_token_stream))) == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0')
	{
		if ((token_len = set_token(buffer + i)) < 0)
		{
			return (-1);
			destroy_stream(stream);
		}
		i += token_len;
	}
	return (stream);
}