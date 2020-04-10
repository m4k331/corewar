/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:29:19 by limry             #+#    #+#             */
/*   Updated: 2020/02/25 20:29:21 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap.h"

void				bin_heap_free(t_bin_heap *heap)
{
	if (!heap)
		return ;
	if (heap->nodes)
		free(heap->nodes);
	free(heap);
}
