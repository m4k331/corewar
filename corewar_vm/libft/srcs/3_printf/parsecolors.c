/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecolors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:25:28 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_parsecolornorm(const char *str, t_rules *rules)
{
	if (*(++str) == 'r')
		rules->color = RED;
	else if (*str == 'g')
		rules->color = GREEN;
	else if (*str == 'y')
		rules->color = YELLOW;
	else if (*str == 'b')
		rules->color = BLUE;
	else if (*str == 'm')
		rules->color = MAGENTA;
	else if (*str == 'c')
		rules->color = CYAN;
	if (ft_strlen(rules->color))
		return (1);
	return (0);
}

static int		ft_parsecolorbold(const char *str, t_rules *rules)
{
	if (*(++str) == 'r')
		rules->color = REDBOLD;
	else if (*str == 'g')
		rules->color = GREENBOLD;
	else if (*str == 'y')
		rules->color = YELLOWBOLD;
	else if (*str == 'b')
		rules->color = BLUEBOLD;
	else if (*str == 'm')
		rules->color = MAGENTABOLD;
	else if (*str == 'c')
		rules->color = CYANBOLD;
	if (ft_strlen(rules->color))
		return (1);
	return (0);
}

const char		*ft_parsecolor(const char *str, t_rules *rules)
{
	if (*str == '{' && *(str + 2) == '}' && ft_parsecolornorm(str, rules))
		return (str + 3);
	else if (*str == '{' && *(str + 2) == 'b' &&
	*(str + 3) == '}' && ft_parsecolorbold(str, rules))
		return (str + 4);
	return (str);
}
