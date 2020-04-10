/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_define_mode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:47:14 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 07:50:34 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_input_define_mode(t_input *input, int num_champs)
{
	if (input->flag_server != 0 && input->flag_dump > 0)
		vm_error("Error: choose server mode or dump flag", input);
	else if (input->flag_server != 0)
		input->mode = ONLINE;
	else
	{
		input->num_champs = num_champs;
		input->mode = OFFLINE;
	}
}
