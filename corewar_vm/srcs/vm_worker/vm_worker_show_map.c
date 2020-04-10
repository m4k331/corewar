/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_show_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:31:23 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:31:57 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

int				vm_worker_show_map(t_worker *worker, int bound)
{
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % bound == 0)
		{
			if (i != 0)
				ft_printf("\n");
			ft_printf("%06#x: ", i);
		}
		else
			ft_printf(" ");
		ft_printfd(worker->io->cout, "%02x", worker->map[i]);
		i++;
	}
	ft_printfd(worker->io->cout, "\n");
	return (1);
}
