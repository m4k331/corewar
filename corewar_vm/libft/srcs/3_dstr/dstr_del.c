/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:41:08 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 09:41:08 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dstr.h"

void			dstr_del(t_dstr *str)
{
	if (!str)
		return ;
	free(str->data);
	str->data = NULL;
	str->start = NULL;
	free(str);
	str = NULL;
}