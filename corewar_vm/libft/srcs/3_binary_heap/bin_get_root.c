/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_get_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:29:30 by limry             #+#    #+#             */
/*   Updated: 2020/02/25 20:29:32 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap.h"

t_bin_node			*bin_get_root(t_bin_heap *heap)
{
	if (heap->num_nodes == 0)
		return (NULL);
	return (&(heap->nodes[1]));
}
