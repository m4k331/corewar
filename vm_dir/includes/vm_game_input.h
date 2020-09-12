/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:24:18 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_GAME_INPUT_H
# define VM_GAME_INPUT_H

# include "corewar_vm.h"

typedef struct		s_champ
{
	uint8_t			id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	int				code_size;
	char			code[CHAMP_MAX_SIZE];
}					t_champ;

typedef struct		s_gminput
{
	uint32_t		game_id;
	uint8_t			num_players;
	t_champ			players[4];
}					t_gminput;

typedef struct		s_header_new
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH];
	unsigned int	null_name;
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH];
	unsigned int	null_comment;
}					t_header_new;

int					vm_input_parse_champ_offline(int fd, t_champ *champ,
					t_input *input);
int					vm_input_parse_champ_online(t_champ *champ,
					uint8_t *raw_data, int err_fd);
void				vm_input_create_queue(t_input *input);
t_gminput			*vm_input_av_parse(t_input *input);
int					vm_input_recieve_data(t_input *input);
int					vm_input_socket_is_game_received(t_input *input);

#endif
