/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 12:18:59 by rnarbo            #+#    #+#             */
/*   Updated: 2020/03/02 12:45:25 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_putstr_fd(char *str, int fd)
{
	dprintf(fd, "%s", str);
}

int		usage(char *prog_name)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(prog_name, 2);
	ft_putstr_fd(" champion.s\n", 2);
	ft_putstr_fd("\tchampion file must contain .s extention\n", 2);
	return (-1);
}