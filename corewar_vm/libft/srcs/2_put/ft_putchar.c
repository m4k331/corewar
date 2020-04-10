/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:02:52 by limry             #+#    #+#             */
/*   Updated: 2020/03/05 13:44:15 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

int		ft_putchar(char c)
{
	return (write(1, &c, 1));
}
