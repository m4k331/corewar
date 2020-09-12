/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_worker_manager_init.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:04:05 by limry             #+#    #+#             */
/*   Updated: 2020/07/04 15:30:18 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static t_ops			g_op_tab[16] =
{
	{
		.name = "live",
		.args_num = 1,
		.args_types = {T_DIR, 0, 0},
		.code = 0x01,
		.counter = 10,
		.log_msg = "alive",
		.has_types = FALSE,
		.smth = FALSE,
		.mod_car = FALSE,
		.op = &op_live,
		.dir_size = 4
	},
	{
		.name = "ld",
		.args_num = 2,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.code =0x02,
		.counter = 5,
		.log_msg = "load",
		.has_types = TRUE,
		.smth = FALSE,
		.mod_car = TRUE,
		.op = &op_ld,
		.dir_size = 4
	},
	{
		.name = "st",
		.args_num = 2,
		.args_types = {T_REG, T_IND | T_REG, 0},
		.code =0x03,
		.counter = 5,
		.log_msg = "store",
		.has_types = TRUE,
		.smth = FALSE,
		.mod_car = FALSE,
		.op = &op_st,
		.dir_size = 4
	},
	{
		.name = "add",
		.args_num = 3,
		.args_types = {T_REG, T_REG, T_REG},
		.code = 0x04,
		.counter = 10,
		.log_msg = "addition",
		.has_types = TRUE,
		.smth = FALSE,
		.mod_car = TRUE,
		.op = &op_add,
		.dir_size = 4
	},
	{
		.name = "sub",
		.args_num = 3,
		.args_types = {T_REG, T_REG, T_REG},
		.code = 0x05,
		.counter = 10,
		.log_msg = "soustraction",
		.has_types = TRUE,
		.smth = FALSE,
		.mod_car = TRUE,
		.op = &op_sub,
		.dir_size = 4
	},
	{
		.name = "and",
		.args_num = 3,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.code = 0x06,
		.counter = 6,
		.log_msg = "et (and  r1, r2, r3   r1&r2 -> r3",
		.has_types = TRUE,
		.smth = FALSE,
		.mod_car = TRUE,
		.op = &op_and,
		.dir_size = 4
	},
	{
		.name = "or",
		.args_num = 3,
		.args_types = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.code = 0x07,
		.counter = 6,
		.log_msg = "ou  (or   r1, r2, r3   r1 | r2 -> r3",
		.has_types = TRUE,
		.smth = FALSE,
		.mod_car = TRUE,
		.op = &op_or,
		.dir_size = 4
	},
	{
		.name = "xor",
		.args_num = 3,
		.args_types = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.code = 0x08,
		.counter = 6,
		.log_msg = "ou (xor  r1, r2, r3   r1^r2 -> r3",
		.has_types = TRUE,
		.smth = FALSE,
		.mod_car = TRUE,
		.op = &op_xor,
		.dir_size = 4
	},
	{
		.name = "zjmp",
		.args_num = 1,
		.args_types = {T_DIR, 0, 0},
		.code = 0x09,
		.counter = 20,
		.log_msg = "jump if zero",
		.has_types = FALSE,
		.smth = TRUE,
		.mod_car = FALSE,
		.op = &op_zjmp,
		.dir_size = 2
	},
	{
		.name = "ldi",
		.args_num = 3,
		.args_types = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.code = 0x0A,
		.counter = 25,
		.log_msg = "load index",
		.has_types = TRUE,
		.smth = TRUE,
		.mod_car = FALSE,
		.op = &op_ldi,
		.dir_size = 2
	},
	{
		.name = "sti",
		.args_num = 3,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.code = 0x0B,
		.counter = 25,
		.log_msg = "store index",
		.has_types = TRUE,
		.smth = TRUE,
		.mod_car = FALSE,
		.op = &op_sti,
		.dir_size = 2
	},
	{
		.name = "fork",
		.args_num = 1,
		.args_types = {T_DIR, 0, 0},
		.code =0x0C,
		.counter = 800,
		.log_msg = "fork",
		.has_types = FALSE,
		.smth = TRUE,
		.mod_car = FALSE,
		.op = &op_fork,
		.dir_size = 2
	},
	{
		.name = "lld",
		.args_num = 2,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.code = 0x0D,
		.counter = 10,
		.log_msg = "long load",
		.has_types = TRUE,
		.smth = FALSE,
		.mod_car = TRUE,
		.op = &op_lld,
		.dir_size = 4
	},
	{
		.name = "lldi",
		.args_num = 3,
		.args_types = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.code = 0x0E,
		.counter = 50,
		.log_msg = "long load index",
		.has_types = TRUE,
		.smth = TRUE,
		.mod_car = TRUE,
		.op = &op_lldi,
		.dir_size = 2
	},
	{
		.name = "lfork",
		.args_num = 1,
		.args_types = {T_DIR, 0, 0},
		.code = 0x0F,
		.counter = 1000,
		.log_msg = "long fork",
		.has_types = FALSE,
		.smth = TRUE,
		.mod_car = FALSE,
		.op = &op_lfork,
		.dir_size = 2
	},
	{
		.name = "aff",
		.args_num = 1,
		.args_types = {T_REG, 0, 0},
		.code = 0x10,
		.counter = 2,
		.log_msg = "aff",
		.has_types = TRUE,
		.smth = FALSE,
		.mod_car = FALSE,
		.op = &op_aff,
		.dir_size = 4
	},
};

void						vm_worker_fill_io_interface(t_io_interface *io,
							t_input *input, uint32_t id_wk)
{
	io->address = input->io->address;
	io->port = input->wk_sockets[id_wk];
	vm_socket_fill(&(io->hints));
}

void						vm_worker_set_interface(t_worker *worker,
							t_input *input, uint32_t id_wk)
{
	worker->log = dstr_init(NULL, 100);
	if (!(worker->io = vm_socket_io_init((void *)worker)))
		vm_error("Error: cant create io for worker", input);
	vm_worker_fill_io_interface(worker->io, input, id_wk);
}

void						vm_worker_clean(t_worker *worker)
{
	ft_bzero(worker->map, MEM_SIZE);
	ft_bzero(worker->set, MEM_SIZE);
	darr_clean(worker->carrs, 0);
	worker->ctd = CYCLE_TO_DIE;
	worker->num_live = 0;
	worker->num_checks = 0;
	worker->car_num = 0;
	worker->live_head = -1;
	worker->dead_head = -1;
	worker->gameid = -1;
	worker->ctd = CYCLE_TO_DIE;
}

void						vm_worker_create(t_input *input, uint32_t id_wk)
{
	t_worker				*worker_new;

	if (!(worker_new = malloc(sizeof(t_worker))))
		vm_error("Error: can't create worker for server", input);
	else
	{
		ft_bzero(worker_new, sizeof(t_worker));
		worker_new->id_worker = id_wk;
		worker_new->carrs = darr_init(STRT_CARR_NUM, 0, sizeof(t_car), NULL);
		worker_new->dump = input->flag_dump;
		worker_new->reg_workers = &(input->worker_mngr->reg_workers);
		worker_new->flag_log = input->flag_log;
		worker_new->lib_ops = g_op_tab;
		worker_new->last_lived = 0;
		worker_new->car_num = 0;
		worker_new->cur_ctd = 0;
		vm_worker_clean(worker_new);
		vm_worker_set_interface(worker_new, input, id_wk);
		input->worker_mngr->workers[id_wk] = worker_new;
	}
}

void						vm_worker_manager_init(t_input *input)
{
	t_worker_manager		*new_manager;
	uint32_t				reg_workers;

	if (!(new_manager = malloc(sizeof(t_worker_manager))))
		vm_error("Error: can't create manager server", input);
	input->worker_mngr = new_manager;
	reg_workers = input->mode < 0 ? -input->mode : input->mode;
	input->worker_mngr->reg_workers = 0;
	while (reg_workers--)
		input->worker_mngr->reg_workers |= (1u << reg_workers);
	reg_workers = input->mode < 0 ? -input->mode : input->mode;
	if (!(input->worker_mngr->workers =
				(t_worker**)malloc(sizeof(t_worker*) * reg_workers)))
		vm_error("Error: can't create workers for server", input);
	while (reg_workers--)
		vm_worker_create(input, reg_workers);
}
