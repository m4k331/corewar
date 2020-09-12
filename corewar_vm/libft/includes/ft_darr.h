/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:57:52 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DARR_H
# define FT_DARR_H

# include <stdlib.h>
# include "ft_mem.h"
# include "ft_put.h"

typedef struct			s_darr
{
	void				*data;
	void				*start;
	int64_t				len;
	int64_t				len_data;
	int64_t				cap;
	size_t				unit_size;
	int					err_fd;
}						t_darr;

typedef struct			s_timsort
{
	void				*data;
	int64_t				len;
}						t_timsort;

typedef struct			s_darr_binargs
{
	int					(*comparator)(void *a, void *b);
	void				*to_find;
	uint8_t				is_desc;
}						t_darr_binargs;

typedef struct			s_darr_binframes
{
	int64_t				start;
	int64_t				end;
}						t_darr_binframes;

typedef struct			s_darr_binsearch
{
	t_darr_binargs		ba;
	t_darr_binframes	bf;
}						t_darr_binsearch;

typedef struct			s_mgrindex
{
	int64_t				mid;
	int64_t				buf;
	int64_t				i;
	int64_t				ir;
	int64_t				il;
	int64_t				end;
}						t_mgrindex;

t_darr					*darr_init(int64_t cap, int64_t len,
						size_t unit_size, void *data);
t_darr					*darr_clean(t_darr *darr, int unset_fd_mode);
void					darr_delete(t_darr *darr);
t_darr					*darr_join(t_darr *darr, void *data,
						int64_t len_units, size_t unit_size);
void					*darr_pop_all(t_darr *darr, void **res);
void					*darr_pop_front(t_darr *darr, void **res,
						int64_t len_units);
void					*darr_pop_back(t_darr *darr, void **res,
						int64_t len_units);
void					darr_remove_back(t_darr *darr, int64_t l);
void					darr_remove_front(t_darr *darr, int64_t l);
void					darr_unset_err_fd(t_darr *darr);
void					darr_set_err_fd(t_darr *darr, int fd);
void					*darr_pop_back_wo_mal(t_darr *darr, void *res,
						int64_t len_units);
void					*darr_pop_front_wo_mal(t_darr *darr, void *res,
						int64_t len_units);
void					*darr_pop_all_wo_mal(t_darr *darr, void *res);
void					darr_shrink(t_darr *darr);
void					darr_del_ith(t_darr *darr, int64_t i,
						int64_t num_units_to_del);
void					ft_darr_timsort(t_darr *darr,
						int (comparator)(void *a, void *b));
int64_t					ft_merge_batches(t_darr *d, t_timsort bl, t_timsort br,
						int (comparator)(void *a, void *b));
void					merge_instant(t_darr *darr, int64_t *indx,
						t_timsort *stack, int (comparator)(void *a, void *b));
void					*darr_bin_search(t_darr *d, void *start_run,
						int64_t len_mem, t_darr_binargs ba);
int64_t					darr_timsort_getrun(t_darr *darr, void *start_run,
						int64_t minrun_mem, int (*compare)(void *, void *));

#endif
