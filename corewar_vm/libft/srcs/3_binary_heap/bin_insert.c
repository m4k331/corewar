/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:29:45 by limry             #+#    #+#             */
/*   Updated: 2020/06/05 14:43:35 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap.h"

int				bin_heap_insert(t_bin_heap *heap, void *data, int64_t key)
{
	if (heap->num_nodes > heap->capacity)
		return (0);
	(heap->nodes + heap->num_nodes)->data = data;
	(heap->nodes + heap->num_nodes)->key = key;
	bin_heap_restore(heap);
	heap->num_nodes++;
	return (1);
}
