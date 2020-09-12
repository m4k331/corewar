/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:48:22 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:48:26 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			error_no_label(t_data *data, t_token *arg, char *c)
{
	ft_putstr_fd(ERROR_NO_LABEL, 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd(" while attempting to dereference token [TOKEN][", 2);
	ft_putnbr_fd(arg->line_num, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(data->current_token->char_num + 1, 2);
	ft_putstr_fd("] ", 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd(arg->type, 2);
	ft_putstr_fd(" \":", 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd("\"\n", 2);
	return (0);
}

int			error_args_count(t_data *data)
{
	ft_putstr_fd(ERROR_INVALID_ARGS_COUNT, 2);
	ft_putstr_fd(data->current_token->content, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int			error_invalid_arg(t_data *data, t_token *arg, int num)
{
	int		i;

	i = 0;
	ft_putstr_fd(ERROR_INVALID_ARG, 2);
	ft_putnbr_fd(num, 2);
	ft_putstr_fd(" type ", 2);
	while (arg->type[i])
		ft_putchar_fd((char)ft_tolower(arg->type[i++]), 2);
	i = 0;
	ft_putstr_fd(" for instruction ", 2);
	while (data->current_token->content[i])
		ft_putchar_fd((char)ft_tolower(data->current_token->content[i++]), 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int			error_instruction(t_data *data)
{
	ft_putstr_fd(ERROR_INVALID_INSTRUCTION, 2);
	ft_putchar_fd('[', 2);
	ft_putnbr_fd(data->current_token->line_num, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(data->current_token->char_num + 1, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd(data->current_token->type, 2);
	ft_putstr_fd(" \"", 2);
	ft_putstr_fd(data->current_token->content, 2);
	ft_putstr_fd("\"\n", 2);
	return (0);
}

int			error(t_data *data)
{
	ft_putstr_fd(ERROR_SYNTAX, 2);
	ft_putchar_fd('[', 2);
	ft_putnbr_fd(data->current_token->line_num, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(data->current_token->char_num + 1, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd(data->current_token->type, 2);
	if (ft_strcmp(data->current_token->type, "ENDLINE"))
	{
		ft_putstr_fd(" \"", 2);
		ft_putstr_fd(data->current_token->content, 2);
		ft_putstr_fd("\"\n", 2);
	}
	else
		ft_putchar_fd('\n', 2);
	return (0);
}
