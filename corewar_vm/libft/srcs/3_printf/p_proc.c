/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_proc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:01:30 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		set_start(t_rules *rules, long long *strt)
{
	rules->len_num = rules->prec_on ? 2 : 3;
	rules->len_word = rules->width ? rules->width : rules->len_num;
	rules->len_word = rules->prec + 2 > rules->len_word ?
			rules->prec + 2 : rules->len_word;
	if (rules->flags & 4)
		*strt = 0;
	else
	{
		if (rules->prec_on)
			*strt = rules->len_word - rules->len_num - rules->prec;
		else
			*strt = rules->len_word - rules->len_num;
	}
}

static char		*pf_procnull(t_rules *rules)
{
	char		*mem;
	long long	strt;

	set_start(rules, &strt);
	mem = ft_strnew(rules->len_word);
	ft_memset(mem, ' ', rules->len_word);
	mem[strt] = '0';
	mem[strt + 1] = 'x';
	if (rules->prec_on)
		ft_memset(mem + (rules->len_word - rules->prec), '0', rules->prec);
	else
		mem[strt + 2] = '0';
	return (mem);
}

static void		pf_definelenword(t_rules *rules)
{
	if (rules->prec_on)
		if (rules->len_num < rules->prec)
			rules->len_num = rules->prec;
	if (rules->width < 16)
		rules->len_word = (rules->width > rules->len_num + 2 ?
				rules->width : rules->len_num + 2);
	else
		rules->len_word = rules->width;
}

static void		pf_procother(t_rules *rules, void *pointer, char **mem)
{
	long int	addr;
	size_t		i;

	addr = (long)pointer;
	while (addr /= 16)
		rules->len_num++;
	pf_definelenword(rules);
	i = ((rules->flags & 4) ? 2 + rules->len_num : rules->len_word);
	*mem = ft_strnew(rules->len_word);
	ft_memset(*mem, ' ', rules->len_word);
	addr = (long)pointer;
	while (addr || rules->len_num)
	{
		if ((addr % 16) > 9)
			(*mem)[--i] = 'a' + addr % 16 % 10;
		else
			(*mem)[--i] = '0' + addr % 16;
		addr /= 16;
		rules->len_num--;
	}
	if (rules->flags & 2 && !(rules->flags & 4) && rules->width > 0)
		while (i > 1)
			(*mem)[i--] = '0';
	(*mem)[--i] = 'x';
	(*mem)[--i] = '0';
}

void			p_writer(void *pointer, t_rules *rules, char **mem)
{
	if (pointer == NULL)
		*mem = pf_procnull(rules);
	else
		pf_procother(rules, pointer, mem);
}
