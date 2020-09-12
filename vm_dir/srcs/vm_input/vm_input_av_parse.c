/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_av_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:58:04 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:58:04 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"
#include "vm_game_input.h"

static int			vm_check_file_name(char *file_name, t_input *input)
{
	size_t			len_name;

	if (file_name == NULL)
		return (0);
	len_name = ft_strlen(file_name);
	if (len_name < 5 || ft_strcmp(file_name + len_name - 4, ".cor"))
	{
		ft_printfd(input->io->err_fd, "ERROR: can't read file %s\n",
				file_name);
		vm_error("VM is closed.", input);
	}
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
		vm_error("Error: no champions", input);
	while (++i < MAX_PLAYERS)
		if (vm_check_file_name(input->champ_files[i], input))
		{
			if ((fd = open(input->champ_files[i], O_RDONLY)) < 0)
				vm_error("Error: the champ file cannot be opened", input);
			if (vm_input_parse_champ_offline(fd, new_game.players + i, input))
				vm_error("Error: can't parse champ file", input);
			close(fd);
			new_game.players[i].id = i + 1;
			new_game.num_players++;
		}
	darr_join(input->games_input_queue, &new_game, 1, sizeof(t_gminput));
	return (input->games_input_queue->data + input->games_input_queue->len);
}
