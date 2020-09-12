/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_name_or_comment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:30:59 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/28 13:31:03 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_name_or_comment(t_data *data, char *line)
{
	if (!ft_strncmp(line + data->char_num, ".name", 5))
	{
		if (!init_token(data, line, NAME, 5))
		{
			ft_putstr_fd(ERROR_MEMORY_ALLOCATION, 2);
			return (0);
		}
		data->char_num += 5;
		return (1);
	}
	else if (!ft_strncmp(line + data->char_num, ".comment", 8))
	{
		if (!init_token(data, line, NAME_COMMENT, 8))
		{
			ft_putstr_fd(ERROR_MEMORY_ALLOCATION, 2);
			return (0);
		}
		data->char_num += 8;
		return (1);
	}
	else
		return (0);
}
