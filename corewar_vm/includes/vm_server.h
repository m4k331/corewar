/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:18:02 by limry             #+#    #+#             */
/*   Updated: 2020/09/12 13:09:26 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_VM_SERVER_H
# define VM_VM_SERVER_H

# include <sys/socket.h>
# include <netinet/tcp.h>
# include <sys/ioctl.h>
# include "corewar_vm.h"

# define STRT_CARR_NUM	4
# define BSIZE_REG		1
# define BSIZE_IND		2
# define LOG_LIVE		1u
# define LOG_CYCLE		2u
# define LOG_OP			4u
# define LOG_DEATH		8u
# define LOG_MOVE		16u
# define LOG_MAP		32u

# define KEEPALIVE_ON	1
# define KEEPALIVE_IDLE	1
# define KEEPALIVE_INTL	1
# define KEEPALIVE_MAXP	10

# ifndef TCP_KEEPIDLE
#  define TCP_KEEPIDLE TCP_KEEPALIVE
# endif

void					vm_server_start(t_input *input);
void					vm_server_run(t_input *input, pthread_attr_t *tattr);
int						vm_parse_byte_to_32int(uint32_t *data, int size);
int32_t					vm_get_addr(int32_t address);
void					vm_worker_manager_remove(t_input *input);

/*
** server part
*/

void					vm_server_thread_attr_set(pthread_attr_t *tattr,
						int mode);
void					vm_server_wait_for_threads(t_input *input, int mode);
void					vm_server_thread_attr_destroy(pthread_attr_t *tattr);
void					vm_server_mode_multithread(t_input *input);

/*
** general input part
*/
t_input					*vm_init_input(int ac, char **av);

void					vm_input_define_mode(t_input *input, int num_champs);
void					vm_input_remove(t_input *input);

/*
** worker part
*/

void					vm_worker_manager_init(t_input *input);
void					vm_worker_log_dead_proc(t_worker *wk);
void					vm_worker_winner_notify(t_worker *wk);
void					vm_worker_socket_notify(t_worker *wk);
void					vm_worker_game_state_notify(t_worker *wk);
void					vm_worker_clean(t_worker *worker);
void					vm_worker_get_data_from_queue(t_worker *worker,
						t_darr *vm_input_queue);
void					*vm_worker_run(void *worker);
void					vm_worker_fill_io_interface(t_io_interface *io,
						t_input *input, uint32_t id_wk);
int						vm_worker_show_map(t_worker *worker, int bound);

/*
** carraige part
*/

t_car					*vm_car_play(t_car *car, t_worker *worker);
void					vm_car_move(t_car *car, t_worker *wk);
int						vm_car_move_log(t_car *car, t_worker *wk);
void					vm_car_get_types_and_step(t_ops op, uint8_t types_byte,
						int32_t args[6], t_car *car);

/*
** list of operations
*/

t_car					*vm_car_implement_op(t_car *car, t_worker *wk);
t_car					*op_live(t_car *car, t_worker *wk,
						int args_3t_3l[6]);
t_car					*op_ld(t_car *car, t_worker *wk, int ar_3t_3l[6]);
t_car					*op_st(t_car *car, t_worker *wk, int ar_3t_3l[6]);
t_car					*op_add(t_car *car, t_worker *wk,
						int ar_3t_3l[6]);
t_car					*op_sub(t_car *car, t_worker *wk, int args[6]);
t_car					*op_and(t_car *car, t_worker *wk,
						int ar_3t_3l[6]);
t_car					*op_or(t_car *car, t_worker *wk, int ar_3t_3l[6]);
t_car					*op_xor(t_car *car, t_worker *wk,
						int ar_3t_3l[6]);
t_car					*op_zjmp(t_car *car, t_worker *wk, int args[6]);
t_car					*op_ldi(t_car *car, t_worker *wk,
						int qr_3t_3l[6]);
t_car					*op_sti(t_car *car, t_worker *wk, int args[6]);
t_car					*op_fork(t_car *car, t_worker *wk, int args[6]);
t_car					*op_lld(t_car *car, t_worker *wk, int args[6]);
t_car					*op_lldi(t_car *car, t_worker *wk, int args[6]);
t_car					*op_lfork(t_car *car, t_worker *wk, int args[6]);
t_car					*op_aff(t_car *car, t_worker *wk, int args[6]);
int						vm_op_get_val(t_worker *wk, t_car *car,
						const int *arg, int offset_cut[2]);
int						vm_op_byte_to_32int(uint8_t *data_start,
						int32_t pos, int32_t size);
void					vm_op_from_int32_to_byte(uint8_t *data_start,
						int num, int32_t pos, int32_t size);
void					vm_op_log(t_car *car, int v[3],
						int ar_3t_3l[6], t_worker *wk);
void					vm_op_set_val_to_byte(uint8_t *data_start,
						uint8_t setter, int32_t pos, int32_t size);
void					op_fork_set_pos_fork(t_car *car,
						t_car *from, int v1, t_worker *wk);
void					op_fork_set_pos_lfork(t_car *car,
						t_car *from, int v1, t_worker *wk);
void					vm_fork_op_have_dead_head(t_worker *wk,
						t_car *car, int v[3], void (set_pos)(t_car *car,
						t_car *from, int v1, t_worker *wk));
t_car					*vm_fork_op_nop_dead_head(t_worker *wk,
						t_car *car, int *v, void (set_pos)(t_car *car,
						t_car *from, int v1, t_worker *wk));

/*
** commands part
*/

int						vm_input_listen_command(t_input *input);
int						vm_command_check_args(char *args, t_io_interface *io);
int						vm_command_not_exists(t_io_interface *io);
int						vm_command_connect(char *args, t_io_interface *input);
int						vm_command_connect_parse(char *args,
						t_io_interface *io);
int						vm_command_connect_workers(t_io_interface *io);
void					vm_command_io_clean(t_io_interface *io);
int						vm_command_disconnect(t_io_interface *io);
int						vm_command_help(t_io_interface *input);
int						vm_command_help_log(t_io_interface *io);
void					vm_command_exit(t_io_interface *io);
int						vm_command_wksetlog(char *args, t_io_interface *io);
int						vm_command_status(t_io_interface *io);
int						vm_command_handshake_send(t_io_interface *io);
int						vm_command_handshake_recv(t_io_interface *io);
void					vm_connect_socket_setup(t_io_interface *io);

/*
** messages part
*/

void					vm_message_set_header(uint8_t type,
						int game_id, int len_msg, t_darr *buffer);
void					vm_message_champs_present(t_worker *wk);
void					vm_message_sendgame(t_worker *wk);
void					vm_message_operation(t_worker *wk, t_car *car);
void					vm_message_proc_statuses(t_worker *wk);
void					vm_message_endgame(t_worker *wk);
void					vm_message_game_loaded(t_worker *wk, t_input *input);

#endif
