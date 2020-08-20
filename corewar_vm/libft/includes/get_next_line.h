/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:29:52 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include "ft_dstr.h"
# include "ft_string.h"

# define BUFF_SIZE 128

typedef struct		s_lst
{
	struct s_lst	*next;
	int				dn;
	uint64_t		rot;
	char			*nl;
	t_dstr			*str;
}					t_lst;

int					get_next_line(const int fd, char **line);
int					clean_all_gnl(t_lst *lst);

#endif
