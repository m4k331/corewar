/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:53:57 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

void			darr_set_err_fd(t_darr *darr, int fd)
{
	darr->err_fd = fd;
}

void			darr_unset_err_fd(t_darr *darr)
{
	darr->err_fd = 2;
}

t_darr			*darr_clean(t_darr *darr, int unset_fd_mode)
{
	darr->len_data = 0;
	darr->len = 0;
	darr->start = darr->data;
	ft_bzero(darr->start, darr->len * darr->unit_size);
	if (unset_fd_mode)
		darr_unset_err_fd(darr);
	return (darr);
}

static t_darr	*darr_malloc_darr(int64_t cap_units, int64_t len_units,
				size_t unit_size)
{
	t_darr		*new;

	if (unit_size == 0)
	{
		ft_putstr_fd("Error: unit size is zero\n", 2);
		return (NULL);
	}
	if (!(new = (t_darr*)malloc(sizeof(t_darr))))
	{
		ft_putstr_fd("Error: can't allocate mem for darr\n", 2);
		return (NULL);
	}
	cap_units = cap_units ? cap_units : 4;
	while (cap_units < len_units)
		cap_units <<= 1;
	new->cap = cap_units;
	return (new);
}

t_darr			*darr_init(int64_t cap_units, int64_t len_units,
				size_t unit_size, void *data)
{
	t_darr		*new;

	if (!(new = darr_malloc_darr(cap_units, len_units, unit_size)))
		return (NULL);
	darr_unset_err_fd(new);
	if (!(new->data = malloc(new->cap * unit_size)))
	{
		free(new);
		ft_putstr_fd("Error: can't malloc mem for data\n", new->err_fd);
		return (NULL);
	}
	new->unit_size = unit_size;
	darr_clean(new, 0);
	if (data)
	{
		new->len = len_units;
		new->len_data = len_units;
		ft_memcpy(new->start, data, len_units * unit_size);
	}
	return (new);
}
