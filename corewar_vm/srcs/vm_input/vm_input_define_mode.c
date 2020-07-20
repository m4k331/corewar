/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_define_mode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:01:06 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:01:06 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_input_define_mode(t_input *input, int num_champs)
{
	if (input->flag_server != 0 && (input->flag_dump > 0 || num_champs > 0))
		vm_error("Error: choose server mode or dump flag. No champs.", input);
	else if (input->flag_server != 0)
		input->mode = ONLINE;
	else
	{
		input->num_champs = num_champs;
		input->mode = OFFLINE;
	}
}
