/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_inc_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:29:37 by limry             #+#    #+#             */
/*   Updated: 2020/06/05 14:43:35 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap.h"

int				bin_inc_key(t_bin_heap *heap, int64_t i, int64_t key)
{
	if (heap->nodes[i].key > key)
		return (-1);
	(&heap->nodes[i])->key = key;
	while (i > 1 && heap->nodes[i].key > heap->nodes[i / 2].key)
	{
		bin_heap_swap(&heap->nodes[i], &heap->nodes[i / 2]);
		i /= 2;
	}
	return (i);
}

int				bin_decr_key(t_bin_heap *heap, int64_t i, int64_t key)
{
	if (heap->nodes[i].key < key)
		return (-1);
	(&heap->nodes[i])->key = key;
	while (i > 1 && heap->nodes[i].key < heap->nodes[i / 2].key)
	{
		bin_heap_swap(&heap->nodes[i], &heap->nodes[i / 2]);
		i /= 2;
	}
	return (i);
}
