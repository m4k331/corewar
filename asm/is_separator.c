/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:51:01 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:51:03 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_separator(t_data *data, char *line)
{
	if (init_token(data, line, 5, 1))
	{
		data->char_num++;
		return (1);
	}
	return (0);
}
