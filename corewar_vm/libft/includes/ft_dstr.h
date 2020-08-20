/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:28:21 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DSTR_H
# define FT_DSTR_H

# include <stdlib.h>
# include <inttypes.h>
# include "ft_mem.h"
# include "ft_string.h"

typedef struct		s_dstr
{
	char			*data;
	char			*start;
	uint64_t		len;
	uint64_t		len_data;
	uint64_t		cap;
}					t_dstr;

void				dstr_del(t_dstr *str);
t_dstr				*dstr_init(char *data, uint64_t cap);
t_dstr				*dstr_joinstr(t_dstr *dstr, char *s);
char				*dstr_pop_front(t_dstr *dstr, char **res, uint64_t l);
char				*dstr_pop_back(t_dstr *dstr, char **res, uint64_t l);
void				dstr_remove_back(t_dstr *dstr, uint64_t l);
void				dstr_remove_front(t_dstr *dstr, uint64_t l);
t_dstr				*dstr_joinstr_len(t_dstr *dstr, char *s,
					uint64_t slen_data);

#endif
