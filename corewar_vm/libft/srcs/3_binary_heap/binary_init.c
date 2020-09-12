/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:30:07 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap.h"
#include "libft.h"

void			bin_clean_heap_data(t_bin_heap *heap)
{
	ft_bzero(heap->nodes, sizeof(t_bin_node) * (heap->capacity + 1));
	heap->num_nodes = 1;
}

t_bin_heap		*bin_heap_init(int64_t size)
{
	t_bin_heap	*heap;

	heap = (t_bin_heap*)malloc(sizeof(t_bin_heap));
	if (!heap)
		return (NULL);
	heap->capacity = size;
	heap->nodes = (t_bin_node*)malloc(sizeof(t_bin_node) * (size + 1));
	if (!heap->nodes)
	{
		free(heap);
		return (NULL);
	}
	bin_clean_heap_data(heap);
	return (heap);
}
