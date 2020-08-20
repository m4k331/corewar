/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:41:23 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dstr.h"

static void		dstr_expand(t_dstr *dstr, uint64_t len_s, char *s)
{
	uint64_t	new_cap;
	char		*new;

	new_cap = dstr->cap;
	while (new_cap <= len_s + dstr->len)
		new_cap <<= 1;
	new = ft_strnew(new_cap);
	ft_bzero(new, new_cap);
	if (dstr->data)
		ft_memmove(new, dstr->start, dstr->len_data);
	ft_memmove(new + dstr->len_data, s, len_s);
	free(dstr->data);
	dstr->data = new;
	dstr->cap = new_cap;
	dstr->start = dstr->data;
	dstr->len_data = dstr->len_data + len_s;
	dstr->len = dstr->len_data;
}

t_dstr			*dstr_joinstr(t_dstr *dstr, char *s)
{
	uint64_t	len_s;

	if (!s)
		return (dstr);
	len_s = ft_strlen(s);
	if (len_s + dstr->len >= dstr->cap)
	{
		if (len_s < dstr->len - dstr->len_data)
		{
			ft_memmove(dstr->data, dstr->start, dstr->len_data + 1);
			dstr->start = dstr->data;
			ft_strlcat(dstr->data + dstr->len_data, s,
				dstr->cap - dstr->len_data);
			dstr->len_data += len_s;
			dstr->len = dstr->len_data;
		}
		else
			dstr_expand(dstr, len_s, s);
		return (dstr);
	}
	ft_strlcat(dstr->start + dstr->len_data, s, len_s + 1);
	dstr->len += len_s;
	dstr->len_data += len_s;
	return (dstr);
}

t_dstr			*dstr_joinstr_len(t_dstr *dstr, char *s, uint64_t slen_data)
{
	if (!s || slen_data == 0)
		return (dstr);
	if (slen_data + dstr->len >= dstr->cap)
	{
		if (slen_data < dstr->len - dstr->len_data)
		{
			ft_memmove(dstr->data, dstr->start, dstr->len_data + 1);
			dstr->start = dstr->data;
			ft_strlcat(dstr->data + dstr->len_data, s,
				dstr->cap - dstr->len_data);
			dstr->len_data += slen_data;
			dstr->len = dstr->len_data;
		}
		else
			dstr_expand(dstr, slen_data, s);
		return (dstr);
	}
	ft_strlcat(dstr->start + dstr->len_data, s, slen_data + 1);
	dstr->len += slen_data;
	dstr->len_data += slen_data;
	return (dstr);
}
