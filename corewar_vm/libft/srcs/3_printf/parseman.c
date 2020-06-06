/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseman.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:45:46 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_darr.h"

const char			*ft_parse(const char *str, va_list *arg, t_rules *rules)
{
	char			*res;
	ssize_t			check;

	res = pf_rulesinit(rules, &str, arg);
	if (!rules->skip && rules->len_word)
	{
		ft_putstr_fd(rules->color, rules->fd);
		check = write(rules->fd, res, rules->len_word);
		free(res);
		if (0 > check)
		{
			rules->len_word = -1;
			rules->err = 1;
			return (NULL);
		}
		if (rules->color[0] != '\0')
			ft_putstr_fd(RESET, rules->fd);
	}
	if (!rules->skip && *str)
		str++;
	return (str);
}

const char			*ft_parse_s(const char *str, va_list *arg, t_rules *rules)
{
	char			*res;

	res = pf_rulesinit(rules, &str, arg);
	if (!rules->skip && rules->len_word)
	{
		dstr_joinstr(rules->dstr, rules->color);
		dstr_joinstr_len(rules->dstr, res, rules->len_word);
		free(res);
		if (rules->color[0] != '\0')
			dstr_joinstr(rules->dstr, RESET);
	}
	if (!rules->skip && *str)
		str++;
	return (str);
}
