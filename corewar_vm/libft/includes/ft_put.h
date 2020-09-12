/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:29:20 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUT_H
# define FT_PUT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_mem.h"
# include "ft_string.h"

int				ft_putchar(char c);
int				ft_putnbr(int n);
int				ft_putstr(char const *s);
int				ft_putendl(char const *s);
int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char const *s, int fd);
int				ft_putendl_fd(char const *s, int fd);
int				ft_putnbr_fd(int n, int fd);

#endif
