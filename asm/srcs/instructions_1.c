/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:49:08 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:49:21 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			op_and_or_xor(t_data *data)
{
	t_token	*arg;
	int		args_calc;

	args_calc = 0;
	arg = data->current_token->args;
	while (arg)
	{
		args_calc++;
		if (args_calc > 3)
			return (error_invalid_arg(data, arg, args_calc - 1));
		if ((args_calc == 1 || args_calc == 2)
				&& ft_strncmp(arg->type, "INDIRECT", 8)
				&& ft_strcmp(arg->type, "REGISTER")
				&& ft_strncmp(arg->type, "DIRECT", 6))
			return (error_invalid_arg(data, arg, args_calc - 1));
		if (args_calc == 3 && ft_strcmp(arg->type, "REGISTER"))
			return (error_invalid_arg(data, arg, args_calc - 1));
		arg = arg->next;
	}
	if (args_calc < 3)
		return (error_args_count(data));
	return (1);
}

int			op_add_sub(t_data *data)
{
	t_token	*arg;
	int		args_calc;

	args_calc = 0;
	arg = data->current_token->args;
	while (arg)
	{
		args_calc++;
		if (args_calc > 3)
			return (error_invalid_arg(data, arg, args_calc - 1));
		if ((args_calc == 1 || args_calc == 2 || args_calc == 3)
				&& ft_strcmp(arg->type, "REGISTER"))
			return (error_invalid_arg(data, arg, args_calc - 1));
		arg = arg->next;
	}
	if (args_calc < 3)
		return (error_args_count(data));
	return (1);
}

int			op_st(t_data *data)
{
	t_token	*arg;
	int		args_calc;

	args_calc = 0;
	arg = data->current_token->args;
	while (arg)
	{
		args_calc++;
		if (args_calc > 2)
			return (error_invalid_arg(data, arg, args_calc - 1));
		if (args_calc == 1 && ft_strcmp(arg->type, "REGISTER"))
			return (error_invalid_arg(data, arg, args_calc - 1));
		if (args_calc == 2 && ft_strncmp(arg->type, "INDIRECT", 8)
				&& ft_strcmp(arg->type, "REGISTER"))
			return (error_invalid_arg(data, arg, args_calc - 1));
		arg = arg->next;
	}
	if (args_calc < 2)
		return (error_args_count(data));
	return (1);
}

int			op_ld_lld(t_data *data)
{
	t_token	*arg;
	int		args_calc;

	args_calc = 0;
	arg = data->current_token->args;
	while (arg)
	{
		args_calc++;
		if (args_calc > 2)
			return (error_invalid_arg(data, arg, args_calc - 1));
		if (args_calc == 1 && ft_strncmp(arg->type, "DIRECT", 6)
				&& ft_strncmp(arg->type, "INDIRECT", 8))
			return (error_invalid_arg(data, arg, args_calc - 1));
		if (args_calc == 2 && ft_strcmp(arg->type, "REGISTER"))
			return (error_invalid_arg(data, arg, args_calc - 1));
		arg = arg->next;
	}
	if (args_calc < 2)
		return (error_args_count(data));
	return (1);
}

int			op_live_zjmp_fork_lfork(t_data *data)
{
	t_token	*arg;
	int		args_calc;

	args_calc = 0;
	arg = data->current_token->args;
	while (arg)
	{
		args_calc++;
		if (args_calc > 1)
			return (error_invalid_arg(data, arg, args_calc - 1));
		if (ft_strncmp(arg->type, "DIRECT", 6))
			return (error_invalid_arg(data, arg, args_calc - 1));
		arg = arg->next;
	}
	return (1);
}
