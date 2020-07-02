/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:06:43 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:06:43 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include "vm_server.h"
#include "vm_game_input.h"

void			main_show_msg(void)
{
	ft_putstr_fd(MSG_NO_ARGS0, 2);
	ft_putstr_fd(MSG_NO_ARGS1, 2);
	ft_putstr_fd(MSG_NO_ARGS2, 2);
	ft_putstr_fd(MSG_NO_ARGS3, 2);
	ft_putstr_fd(MSG_NO_ARGS4, 2);
	ft_putstr_fd(MSG_NO_ARGS5, 2);
	ft_putstr_fd(MSG_NO_ARGS6, 2);
	ft_putstr_fd(MSG_NO_ARGS7, 2);
	ft_putstr_fd(MSG_NO_ARGS8, 2);
	ft_putstr_fd(MSG_NO_ARGS9, 2);
	ft_putstr_fd(MSG_NO_ARGS10, 2);
	ft_putstr_fd(MSG_NO_ARGS11, 2);
	ft_putstr_fd(MSG_NO_ARGS12, 2);
	ft_putstr_fd(MSG_NO_ARGS13, 2);
	ft_putstr_fd(MSG_HELP_LOG0, 2);
	ft_putstr_fd(MSG_HELP_LOG1, 2);
	ft_putstr_fd(MSG_HELP_LOG2, 2);
	ft_putstr_fd(MSG_HELP_LOG3, 2);
	ft_putstr_fd(MSG_HELP_LOG4, 2);
	ft_putstr_fd(MSG_HELP_LOG5, 2);
	vm_error(MSG_HELP_LOG6, NULL);
}

int				main(int ac, char *av[])
{
	t_input		*input;

	if (ac == 1)
		main_show_msg();
	if (!(input = vm_init_input(ac, av)))
	{
		ft_putstr_fd("Error: cant start program\n", 2);
		return (1);
	}
	vm_input_define(input);
	vm_input_create_queue(input);
	vm_server_start(input);
	vm_input_remove(input);
	return (0);
}
