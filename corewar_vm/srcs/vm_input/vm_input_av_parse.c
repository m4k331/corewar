/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_to_queue.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:57:12 by limry             #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"
#include "vm_game_input.h"

static int			vm_check_file_name(char *file_name)
{
	size_t			len_name;

	if (file_name == NULL)
		return (0);
	len_name = ft_strlen(file_name);
	if (len_name < 5 || ft_strcmp(file_name + len_name - 4, ".cor"))
		return (0);
	return (1);
}

t_gminput			*vm_input_av_parse(t_input *input)
{
	int				i;
	int				fd;
	t_gminput		new_game;

	ft_bzero(&new_game, sizeof(t_gminput));
	i = -1;
	if (input->num_champs == 0)
		vm_error("Error: no champions\n", input);
	while (++i < 4)
		if (vm_check_file_name(input->champ_files[i]))
		{
			if ((fd = open(input->champ_files[i], O_RDONLY)) < 0)
				vm_error("Error: the champ file cannot be opened\n", input);
			if (vm_input_parse_champ_offline(fd, new_game.players + i, input))
				vm_error("Error: can't parse champ file\n", input);
			close(fd);
			new_game.players[i].id = i + 1;
			new_game.num_players++;
		}
	darr_join(input->games_input_queue, &new_game, 1, sizeof(t_gminput));
	return (input->games_input_queue->data + input->games_input_queue->len);
}
