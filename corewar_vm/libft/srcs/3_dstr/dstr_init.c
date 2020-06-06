/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:41:14 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dstr.h"

t_dstr			*dstr_init(char *data, uint64_t cap)
{
	t_dstr		*new;

	new = (t_dstr*)malloc(sizeof(t_dstr));
	new->len = data ? ft_strlen(data) : 0;
	if (!cap)
		cap = 4;
	while (cap < new->len)
		cap <<= 1;
	new->cap = cap;
	new->data = ft_strnew(new->cap);
	new->data[0] = '\0';
	new->start = new->data;
	new->len_data = 0;
	if (data)
		ft_strlcat(new->data, data, new->cap);
	return (new);
}
