/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_socket_parse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:48:44 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:00:12 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_game_input.h"

int						vm_input_socket_parse_game(t_input *input, int game_id)
{
	t_gminput			new_game;
	int					champ_id;
	int					offset;
	int					err_no;

	new_game.game_id = game_id;
	err_no = 0;
	if (4 < (new_game.num_players = *((uint8_t*)input->io->netbuf->start)))
		return (vm_nofity_err(input->io->err_fd, ER_MO_CHMPS, CD_ER_MO_CHMPS));
	champ_id = 0;
	offset = 1;
	while (champ_id < new_game.num_players)
	{
		if ((err_no = vm_input_parse_champ_online(&(new_game.players[champ_id]),
			(uint8_t *)input->io->netbuf->start + offset, input->io->err_fd)))
			break ;
		offset += new_game.players[champ_id].code_size +
				(int)sizeof(t_header_new);
	}
	if (!err_no)
		darr_join(input->games_input_queue, &(new_game),
				1, sizeof(t_gminput));
	return (err_no);
}

int						vm_input_socket_receive_header(t_input *input,
						t_message_header *head)
{
	darr_remove_front(input->io->netbuf, input->io->netbuf->len);
	if (9 != vm_socket_receive_data(input->io, 9))
	{
		ft_printfd(input->io->err_fd, "Error: can't read head data\n");
		return (0);
	}
	head->msg_type = *((uint8_t*)input->io->netbuf->start);
	head->game_id = (int)*((int*)input->io->netbuf->start + 1);
	head->msg_len = (int)*((int*)input->io->netbuf->start + 5);
	return (head->msg_type);
}

int						vm_input_socket_message_receive(t_input *input)
{
	t_message_header	header;

	ft_bzero(&header, sizeof(t_message_header));
	if (!vm_input_socket_receive_header(input, &header))
		return (0);
	darr_remove_front(input->io->netbuf, input->io->netbuf->len);
	if (header.msg_len != vm_socket_receive_data(input->io, header.msg_len))
	{
		ft_printfd(input->io->err_fd, "Error: wrong size of message\n");
		return (0);
	}
	if (header.msg_type == TYPE_GAME_LOADED)
		if (vm_input_socket_parse_game(input, header.game_id))
			return (0);
	return (1);
}

int						vm_input_socket_game_received(t_input *input)
{
	if (input->io->sock_fd > 0)
		return (vm_input_socket_message_receive(input));
	return (0);
}
