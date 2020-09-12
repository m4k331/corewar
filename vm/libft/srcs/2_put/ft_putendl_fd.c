/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:02:45 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

int		ft_putendl_fd(char const *s, int fd)
{
	int	res;

	if ((res = ft_putstr_fd(s, fd)) < 0)
		return (-1);
	if (ft_putchar_fd('\n', fd) < 0)
		return (-1);
	return (res + 1);
}
