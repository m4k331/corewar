/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:02:42 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"

int				ft_putnbr(int n)
{
	long long	num;
	int			res;

	num = (long long)n;
	res = 0;
	if (n < 0)
	{
		if (ft_putchar('-') < 0)
			return (-1);
		res++;
		num *= -1;
	}
	if (num < 10)
	{
		if (ft_putchar(num + '0') < 0)
			return (-1);
		res++;
	}
	else
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	return (res);
}
