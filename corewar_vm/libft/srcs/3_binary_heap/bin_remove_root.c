/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_remove_root.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:29:51 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap.h"

void			bin_heap_heapify(t_bin_heap *heap, int64_t i)
{
	int64_t		l;
	int64_t		r;
	int64_t		min;

	while (1)
	{
		l = 2 * i;
		r = 2 * i + 1;
		min = i;
		if (l <= heap->num_nodes && heap->nodes[l].key < heap->nodes[i].key)
			min = l;
		if (r <= heap->num_nodes && heap->nodes[r].key < heap->nodes[min].key)
			min = r;
		if (min == i)
			break ;
		bin_heap_swap(&heap->nodes[i], &heap->nodes[min]);
		i = min;
	}
}

void			bin_remove_root(t_bin_heap *heap)
{
	if (heap->num_nodes == 1)
		return ;
	heap->num_nodes--;
	heap->nodes[1] = heap->nodes[heap->num_nodes];
	bin_heap_heapify(heap, 1);
}

void			*bin_pop_root(void *data_new_min, t_bin_heap *heap)
{
	data_new_min = bin_get_root(heap)->data;
	bin_remove_root(heap);
	return (data_new_min);
}
