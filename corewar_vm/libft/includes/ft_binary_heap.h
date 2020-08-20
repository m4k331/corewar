/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_heap.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:39:41 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINARY_HEAP_H
# define FT_BINARY_HEAP_H

# include <stdlib.h>
# include <inttypes.h>

typedef struct		s_bin_node
{
	int64_t			key;
	void			*data;
}					t_bin_node;

typedef struct		s_bin_heap
{
	int64_t			capacity;
	int64_t			num_nodes;
	t_bin_node		*nodes;
}					t_bin_heap;

t_bin_heap			*bin_heap_init(int64_t size);
void				bin_heap_free(t_bin_heap *heap);
void				bin_heap_swap(t_bin_node *a, t_bin_node *b);
t_bin_node			*bin_get_root(t_bin_heap *heap);
int					bin_heap_insert(t_bin_heap *heap, void *data, int64_t key);
void				bin_remove_root(t_bin_heap *heap);
int					bin_inc_key(t_bin_heap *heap, int64_t i, int64_t key);
int					bin_decr_key(t_bin_heap *heap, int64_t i, int64_t key);
void				*bin_pop_root(void *new_min, t_bin_heap *heap);
void				bin_clean_heap_data(t_bin_heap *heap);
void				bin_refresh_keys(t_bin_heap *heap, int64_t f(void*));
void				bin_heap_restore(t_bin_heap *heap);
void				bin_heapify(t_bin_heap *heap, int64_t i);
void				bin_heap_heapify(t_bin_heap *heap, int64_t i);

#endif
