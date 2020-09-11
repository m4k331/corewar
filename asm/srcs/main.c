/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:51:45 by dorphan           #+#    #+#             */
/*   Updated: 2020/07/25 14:50:43 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	if (ac == 1)
		ft_putstr(USAGE);
	else if (ac > 2)
		ft_putstr_fd(ERROR_MANY_ARGS, 2);
	else if (check_file_name(av[1]))
		compile(av[1]);
	else
		ft_putstr_fd(ERROR_INVALID_CHAMP_NAME, 2);
	return (0);
}
