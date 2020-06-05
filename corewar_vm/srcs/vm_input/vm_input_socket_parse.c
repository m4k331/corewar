/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_socket_parse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 07:48:44 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 19:11:45 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_game_input.h"

int						vm_input_socket_parse_game(t_input *input, int game_id)
{
	t_gminput			new_game;
	int					champ_id;
	uint8_t				*data_start;
	int					err_no;

	new_game.game_id = game_id;
	err_no = 0;
	data_start = (uint8_t*)input->io->netbuf->start + HEADER_MSG_LEN;
	if (4 < (new_game.num_players =*data_start))
		return (vm_nofity_err(input->io->err_fd, ER_MO_CHMPS, CD_ER_MO_CHMPS));
	champ_id = -1;
	data_start += 1;
	while (++champ_id < new_game.num_players)
	{
		if ((err_no = vm_input_parse_champ_online(&(new_game.players[champ_id]),
			data_start, input->io->err_fd)))
			break ;
		data_start += new_game.players[champ_id].code_size +
				sizeof(t_header_new);
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
	if (9 != vm_socket_receive_data_wait(input->io, 9))
	{
		ft_printfd(input->io->err_fd, "Error: can't read head data\n");
		return (0);
	}
	head->msg_type = *((uint8_t*)input->io->netbuf->start);
	head->game_id = (int)*((uint8_t*)input->io->netbuf->start + 1);
	head->msg_len = (int)*((uint8_t*)input->io->netbuf->start + 5);
	// TODO: delete
	ft_printf("MSG_TYPE: %d, GAME_ID: %d, MSG_LEN: %d\n",
	head->msg_type, head->game_id, head->msg_len);
	return (head->msg_type);
}

int						vm_input_socket_message_receive(t_input *input)
{
	t_message_header	header;
	int					err_no;

	err_no = 0;
	ft_bzero(&header, sizeof(t_message_header));
	if (!vm_input_socket_receive_header(input, &header))
	{
		ft_printfd(input->io->err_fd, "Error: wrong socket header message\n");
		return (CD_ER_WRONG_SOCKET_HEADER_MSG);
	}
	darr_remove_front(input->io->netbuf, input->io->netbuf->len);
	if (header.msg_len !=
	vm_socket_receive_data_wait(input->io, header.msg_len))
	{
		ft_printfd(input->io->err_fd, "Error: wrong size of message\n");
		return (0);
	}
	if (header.msg_type == TYPE_GAME_LOADED)
		if ((err_no = vm_input_socket_parse_game(input, header.game_id)))
		{
			ft_printfd(input->io->err_fd, ER_PROC_PARSE_GAME);
			return (CD_ER_PROC_PARSE_GAME);
		}
	return (0);
}

/*
** This function parse game from hub and if there is no errors
**  then one game was loaded, so we return 1. Otherwise, return 0 - no new games.
*/
int						vm_input_socket_is_game_received(t_input *input)
{
	int					err_no;

	if (input->io->sock_fd > 0)
	{
		if ((err_no = vm_input_socket_message_receive(input)))
			return (0);
		else
			return (1);
	}
	return (0);
}
