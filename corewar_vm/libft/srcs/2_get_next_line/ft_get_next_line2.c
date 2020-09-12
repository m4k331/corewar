/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:52:19 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		del_lsts(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*tmp1;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		if (tmp1->str)
			dstr_del(tmp1->str);
		free(tmp1);
	}
}

int			clean_all_gnl(t_lst *lst)
{
	if (lst)
		del_lsts(lst);
	return (-1);
}
