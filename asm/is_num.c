/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:50:42 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:50:44 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_num(t_data *data, char *line)
{
	int	i;

	i = data->char_num;
	if (line[i] == '-')
		i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (init_token(data, line, 6, i - data->char_num))
	{
		data->char_num = i;
		return (1);
	}
	return (0);
}
