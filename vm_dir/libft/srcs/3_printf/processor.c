/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:16:30 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			f_writer(t_rules *rules, va_list *arg, char **num)
{
	if (rules->mod & 32UL)
		*num = f_proc(
				(long double)va_arg(*arg, long double), rules);
	else if (rules->mod == 640)
		*num = f_proc(
				(long double)va_arg(*arg, long double), rules);
	else
		*num = f_proc(
				(long double)va_arg(*arg, double), rules);
}

void			di_writer(t_rules *rules, va_list *arg, char **num)
{
	if (rules->mod == 0)
		*num = ft_itoa_len(
				(int)va_arg(*arg, int), rules);
	else if (rules->mod == 320)
		*num = ft_itoa_len(
				(char)va_arg(*arg, int), rules);
	else if (rules->mod == 64)
		*num = ft_itoa_len(
				(short int)va_arg(*arg, int), rules);
	else if (rules->mod == 640)
		*num = ft_itoa_long(
				(long long int)va_arg(*arg, long long int), rules);
	else if (rules->mod == 128)
		*num = ft_itoa_long(
				(long int)va_arg(*arg, long int), rules);
	else
		*num = ft_itoa_len((int)va_arg(*arg, int), rules);
}

void			u_writer(t_rules *rules, va_list *arg, char **num)
{
	if (rules->mod == 0)
		*num = ft_itoa_ulen(
				(unsigned int)va_arg(*arg, unsigned int), rules);
	else if (rules->mod == 320)
		*num = ft_itoa_ulen(
				(unsigned char)va_arg(*arg, int), rules);
	else if (rules->mod == 64)
		*num = ft_itoa_ulen(
				(unsigned short int)va_arg(*arg, int), rules);
	else if (rules->mod == 640)
		*num = ft_itoa_ulong(
				(unsigned long long)va_arg(*arg, unsigned long long), rules);
	else if (rules->mod == 128)
		*num = ft_itoa_ulong(
				(unsigned long int)va_arg(*arg, unsigned long int), rules);
	else
		*num = ft_itoa_ulen((unsigned int)va_arg(*arg, unsigned int), rules);
}

void			o_writer(t_rules *rules, va_list *arg, char **num)
{
	if (rules->mod == 0)
		*num = otoa_base_len((int)va_arg(*arg, int),
				8, '0', rules);
	else if (rules->mod == 320)
		*num = otoa_base_hshort((char)va_arg(*arg, int),
				8, '0', rules);
	else if (rules->mod == 64)
		*num = otoa_base_short((short int)va_arg(*arg, int),
				8, '0', rules);
	else if (rules->mod == 640)
		*num = otoa_base_llong((unsigned long long)va_arg(*arg, long long),
				8, '0', rules);
	else if (rules->mod == 128)
		*num = otoa_base_long((unsigned long)va_arg(*arg, long int),
				8, '0', rules);
	else
		*num = otoa_base_len((int)va_arg(*arg, int),
				8, '0', rules);
}

void			x_writer(const char *str, t_rules *rules, va_list *arg,
				char **num)
{
	if (rules->mod == 0)
		*num = itoa_base_len((unsigned int)va_arg(*arg, int),
				16, *str, rules);
	else if (rules->mod == 320)
		*num = itoa_base_short((unsigned char)va_arg(*arg, int),
				16, *str, rules);
	else if (rules->mod == 64)
		*num = itoa_base_short((unsigned short int)va_arg(*arg, int),
				16, *str, rules);
	else if (rules->mod == 640)
		*num = itoa_base_long((unsigned long long)va_arg(*arg, long long),
				16, *str, rules);
	else if (rules->mod == 128)
		*num = itoa_base_long((unsigned long int)va_arg(*arg, long int),
				16, *str, rules);
	else
		*num = itoa_base_len((unsigned int)va_arg(*arg, int),
				16, *str, rules);
}
