/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:23:35 by limry             #+#    #+#             */
/*   Updated: 2020/09/12 13:10:02 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
# define COREWAR_VM_H

# include <sys/poll.h>
# include <stdlib.h>
# include <fcntl.h>
# include <inttypes.h>
# include <libft.h>
# include <pthread.h>
# include "vm_messages.h"
# include "vm_io_interface.h"
# include "op.h"

# define TRUE			1
# define FALSE			0
# define TIMEOUT_INPUT	5000

/*
** OFFLINE and ONLINE const defines number of simultaneously games
** could be played, i.e. number of threads for games.
** As offline mode always plays only one game, its value is one.
** Value for online game is supposed to be number of threads minus one.
*/

# define OFFLINE		-1
# define ONLINE			3

/*
** structure of head is following:
** 1 byte  -  message type
** 4 bytes -  game id
** 4 bytes -  len msg
*/
# define HEADER_MSG_LEN 9

typedef struct			s_short_champ
{
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	int					code_size;
}						t_short_champ;

typedef struct			s_car
{
	uint32_t			program_counter;
	int					reg[REG_NUMBER];
	uint8_t				carry;
	int32_t				last_live;
	int32_t				next;
	int32_t				id;
	uint16_t			position;
	uint16_t			step_size;
	int32_t				op_code;
}						t_car;

/*
** log:
** 		1	- show lives
** 		2	- show current cycle
** 		4	- show operations
** 		8	- show deaths
** 		16	- show movements
** 		32	- show map before every check
*/

typedef struct			s_worker
{
	uint32_t			id_worker;
	uint8_t				map[MEM_SIZE];
	uint8_t				set[MEM_SIZE];
	t_io_interface		*io;
	t_darr				*carrs;
	int32_t				dump;
	uint32_t			*reg_workers;
	int32_t				ctd;
	int32_t				cur_ctd;
	int32_t				num_live;
	int32_t				num_checks;
	int8_t				last_lived;
	int32_t				live_head;
	int32_t				dead_head;
	uint8_t				flag_log;
	t_short_champ		champs[MAX_PLAYERS];
	int32_t				car_num;
	struct s_ops		*lib_ops;
	t_dstr				*log;
	uint32_t			gameid;
}						t_worker;

typedef struct			s_ops
{
	char				*name;
	int8_t				args_num;
	int32_t				args_types[3];
	int8_t				code;
	uint32_t			counter;
	char				*log_msg;
	int8_t				has_types;
	int8_t				smth;
	int8_t				mod_car;
	t_car				*(*op)(t_car*, t_worker*, int[6]);
	int8_t				dir_size;
}						t_ops;

typedef struct			s_worker_manager
{
	uint32_t			reg_workers;
	t_worker			**workers;
}						t_worker_manager;

typedef struct			s_input
{
	int64_t				flag_dump;
	uint64_t			flag_server;
	uint8_t				flag_log;
	t_darr				*games_input_queue;
	t_worker_manager	*worker_mngr;
	int8_t				mode;
	char				*champ_files[4];
	char				**av;
	int					ac;
	uint8_t				num_champs;
	t_io_interface		*io;
	t_dstr				*console_buffer;
	char				*wk_sockets[ONLINE];
	pthread_t			*threads;
	struct pollfd		fds[2];
}						t_input;

/*
** vm_parse_main.c
*/

void					vm_input_define(t_input *input);

/*
** vm_man_error.c
*/

void					vm_error(char *msg, t_input *g);
void					vm_exit(char *msg, t_input *g);
void					main_show_msg(void);

/*
** vm_parse_champ.c
*/

void					vm_parse_champ(char *data, t_input *g,
						int *flag_pos);

/*
** vm_create_game.c
*/

void					vm_create_game_queue(t_input *g, int mode);
int						vm_nofity_err(int fd, char *msg, int code);

#endif
