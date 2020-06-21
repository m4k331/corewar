/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:49:28 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:49:30 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			op_aff(t_data *data)
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
		if (ft_strcmp(arg->type, "REGISTER"))
			return (error_invalid_arg(data, arg, args_calc - 1));
		arg = arg->next;
	}
	return (1);
}

int			op_sti(t_data *data)
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
		if (args_calc == 1 && ft_strcmp(arg->type, "REGISTER"))
			return (error_invalid_arg(data, arg, args_calc - 1));
		if (args_calc == 2 && ft_strncmp(arg->type, "INDIRECT", 8)
					&& ft_strcmp(arg->type, "REGISTER")
					&& ft_strncmp(arg->type, "DIRECT", 6))
			return (error_invalid_arg(data, arg, args_calc - 1));
		if (args_calc == 3 && ft_strcmp(arg->type, "REGISTER")
					&& ft_strncmp(arg->type, "DIRECT", 6))
			return (error_invalid_arg(data, arg, args_calc - 1));
		arg = arg->next;
	}
	if (args_calc < 3)
		return (error_args_count(data));
	return (1);
}

int			op_ldi_lldi(t_data *data)
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
		if (args_calc == 1 && ft_strncmp(arg->type, "INDIRECT", 8)
					&& ft_strcmp(arg->type, "REGISTER")
					&& ft_strncmp(arg->type, "DIRECT", 6))
			return (error_invalid_arg(data, arg, args_calc - 1));
		if (args_calc == 2 && ft_strcmp(arg->type, "REGISTER")
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
