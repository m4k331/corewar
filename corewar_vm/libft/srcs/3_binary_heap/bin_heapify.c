/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_heapify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:49:23 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap.h"

void		bin_refresh_keys(t_bin_heap *heap, int64_t f(void*))
{
	int64_t	i;

	i = heap->num_nodes;
	while (i > 0)
	{
		heap->nodes[i].key = f(heap->nodes[i].data);
		i--;
	}
}

void		bin_heapify(t_bin_heap *heap, int64_t i)
{
	int64_t	lft;
	int64_t	rgh;
	int64_t	lrg;

	lft = 2 * i;
	rgh = 2 * i + 1;
	lrg = i;
	if (lft <= heap->num_nodes && heap->nodes[lft].key > heap->nodes[lrg].key)
		lrg = lft;
	if (rgh <= heap->num_nodes && heap->nodes[rgh].key > heap->nodes[lrg].key)
		lrg = rgh;
	if (lrg != i)
		bin_heap_swap(&(heap->nodes[i]), &(heap->nodes[lrg]));
}

void		bin_heap_restore(t_bin_heap *heap)
{
	int64_t	i;

	i = heap->num_nodes / 2;
	while (i > 0)
	{
		bin_heapify(heap, i);
		i--;
	}
}
