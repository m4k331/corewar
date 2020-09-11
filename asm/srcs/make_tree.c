/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:52:34 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:52:36 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			make_tree(t_data *data)
{
	data->current_token = data->token;
	if (!parse_name_and_comment(data, 1))
		return (0);
	while (data->current_token->next)
	{
		if (!parse_token(data))
			return (0);
	}
	if (!ft_strcmp(data->token->type, "END"))
		return (error(data));
	return (1);
}
