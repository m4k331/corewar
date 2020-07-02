/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_wksetlog.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:59:09 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 15:59:09 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static int			vm_wksetlog_check_id(int *wk_id, char *wk_id_str,
					t_io_interface *io)
{
	char			*tmp;

	tmp = wk_id_str;
	while (*tmp != '\0')
		if (!(ft_isdigit(*tmp++)))
		{
			ft_printfd(io->err_fd, ERR_NO_WK_ID);
			return (CODE_ERR_NO_WK_ID);
		}
	*wk_id = ft_atoi(wk_id_str);
	if (*wk_id < 1 || *wk_id > ONLINE)
	{
		ft_printfd(io->err_fd, ERR_NO_SUCH_WORKER0, *wk_id);
		ft_printfd(io->err_fd, ERR_NO_SUCH_WORKER1, ONLINE);
		return (CODE_ERR_NO_SUCH_WORKER);
	}
	return (0);
}

static int			vm_wksetlog_parse_wk_id(int *wk_id, char *wk_id_str,
					t_io_interface *io, char *args)
{
	if ((vm_command_check_args(wk_id_str, io)))
	{
		vm_command_io_clean(io);
		ft_printfd(io->err_fd, ERR_NO_WK_ID);
		return (CODE_ERR_NO_WK_ID);
	}
	if ((vm_command_check_args(args, io)))
	{
		vm_command_io_clean(io);
		ft_printfd(io->err_fd, ERR_NOLOGMODE);
		return (CD_ER_NOLOGMODE);
	}
	*args = '\0';
	return (vm_wksetlog_check_id(wk_id, wk_id_str, io));
}

static int			vm_wksetlog_parse_logmode(int *log_mode, char *log_str,
					t_io_interface *io, char *args)
{
	char			*tmp;

	if ((vm_command_check_args(log_str, io)))
	{
		vm_command_io_clean(io);
		ft_printfd(io->err_fd, ERR_NOLOGMODE);
		return (CD_ER_NOLOGMODE);
	}
	if (args)
	{
		ft_printfd(io->err_fd, ERR_MANY_ARGS, args);
		return (CODE_ERR_MANY_ARGS);
	}
	if (*(tmp = log_str) == '\0')
		return (vm_nofity_err(io->err_fd, ERR_NOLOGMODE, CD_ER_NOLOGMODE));
	while (*tmp != '\0')
	{
		if (!(ft_isdigit(*tmp++)))
			return (vm_nofity_err(io->err_fd, ERR_NOLOGMODE, CD_ER_NOLOGMODE));
	}
	*log_mode = ft_atoi(log_str);
	return (0);
}

static int			vm_wksetlog_check_wkmanager(t_input *input)
{
	if (!input->worker_mngr)
	{
		ft_printfd(input->io->err_fd, ERR_YET_NO_WORKERS);
		return (CODE_ERR_YET_NO_WORKERS);
	}
	return (0);
}

int					vm_command_wksetlog(char *args, t_io_interface *io)
{
	int				wk_id;
	int				err_num;
	char			*wk_id_str;
	int				log_mode;
	char			*log_str;

	wk_id = ONLINE + 1;
	log_mode = -1;
	if ((err_num = vm_wksetlog_check_wkmanager((t_input*)io->superior)))
		return (err_num);
	if ((err_num = vm_command_check_args(args, io)))
		return (err_num);
	wk_id_str = args;
	args = ft_strchr(wk_id_str, ' ');
	if ((err_num = vm_wksetlog_parse_wk_id(&wk_id, wk_id_str, io, args)))
		return (err_num);
	log_str = args + 1;
	args = ft_strchr(log_str, ' ');
	if ((err_num = vm_wksetlog_parse_logmode(&log_mode, log_str, io, args)))
		return (err_num);
	((t_input*)io->superior)->worker_mngr->workers[wk_id - 1]->flag_log =
			log_mode;
	ft_printfd(io->cout, MSG_WORKER_LOG_SET, wk_id, log_mode);
	return (0);
}
