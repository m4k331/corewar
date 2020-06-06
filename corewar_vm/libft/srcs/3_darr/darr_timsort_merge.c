/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_timsort_merge.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:25:17 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

static void		mgr_init_struct(t_mgrindex *m, t_timsort b1,
				t_timsort b2, t_darr *d)
{
	m->i = 0;
	m->buf = 0;
	m->il = b1.len - d->unit_size;
	m->ir = b2.len - d->unit_size;
}

static void		ft_copy_batch(void *copy_to, void *copy_from,
				int64_t *offset, t_mgrindex *m)
{
	if (!m->buf)
		return ;
	ft_memmove(copy_to - m->buf, copy_from + *offset - m->buf, m->buf);
	*offset -= m->buf;
	m->i += m->buf;
	m->buf = 0;
}

int64_t			ft_merge_batches(t_darr *d, t_timsort bl, t_timsort br,
				int (comparator)(void *a, void *b))
{
	t_mgrindex	m;
	uint8_t		tmp[br.len];
	void		*end;

	mgr_init_struct(&m, bl, br, d);
	end = (bl.data > br.data ? bl.data + bl.len : br.data + br.len);
	ft_memmove(tmp, br.data, br.len);
	while (m.il >= 0 && m.ir >= 0)
	{
		while (m.ir >= m.buf &&
		comparator(tmp + m.ir - m.buf, bl.data + m.il) < 0)
			m.buf += d->unit_size;
		ft_copy_batch(end - m.i, tmp + d->unit_size, &(m.ir), &m);
		while (m.il >= m.buf &&
		comparator(tmp + m.ir, bl.data + m.il - m.buf) >= 0)
			m.buf += d->unit_size;
		ft_copy_batch(end - m.i, bl.data + d->unit_size, &(m.il), &m);
	}
	if (m.ir + d->unit_size > 0)
		ft_memmove(bl.data, tmp, m.ir + d->unit_size);
	return (bl.len + br.len);
}

void			merge_instant(t_darr *darr, int64_t *indx,
				t_timsort *stack, int (comparator)(void *a, void *b))
{
	while (*indx > 0)
	{
		if ((*indx > 1 && stack[*indx - 2].len <= stack[*indx - 1].len) ||
			(*indx > 2 && stack[*indx - 3].len <= stack[*indx - 1].len +
				stack[*indx - 2].len))
		{
			if (stack[*indx - 2].len <= stack[*indx - 1].len)
				stack[*indx - 2].len = ft_merge_batches(darr,
				stack[*indx - 2], stack[*indx - 1], comparator);
			else if (*indx > 2 && stack[*indx - 3].len <
				stack[*indx - 1].len)
			{
				stack[*indx - 3].len = ft_merge_batches(darr,
				stack[*indx - 3], stack[*indx - 2], comparator);
				ft_memmove(stack + *indx - 2, stack + *indx - 1,
				sizeof(t_timsort));
			}
			else
				stack[*indx - 2].len = ft_merge_batches(darr,
				stack[*indx - 2], stack[*indx - 1], comparator);
			*indx -= 1;
		}
		else
			break ;
	}
}
