/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:51:45 by dorphan           #+#    #+#             */
/*   Updated: 2020/06/21 19:12:33 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "network.h"

int		main_old(int ac, char **av)
{
	if (ac == 1)
		ft_putstr(USAGE);
	else if (ac > 2)
		ft_putstr_fd(ERROR_MANY_ARGS, 2);
	// FIXME: ac == 2 избыточно, тк уже были проверки на ac > 2 и ac == 1
	//FIXED
	else if (check_file_name(av[1]))
		compile(av[1]);
	else
		ft_putstr_fd(ERROR_INVALID_CHAMP_NAME, 2);
	return (0);
}

// Заглушка
int	get_options(t_options *opt, int argc, char **argv)
{
	if (argc == 1)
		return (1);
	else if (argc > 2)
		ft_putstr_fd(ERROR_MANY_ARGS, 2);
	else
	{
		opt->filename = argv[1];
		return (0);
	}
	return (1);
}

int checks(t_options *opt, int argc, char **argv)
{
	if (get_options(opt, argc, argv))
		ft_putstr_fd(USAGE, 2);
	else if (opt->server == 1 || check_file_name(opt->filename) == 0)
		return (0);
	return (1);
}

// Заглушка
int network(t_options *opt)
{
	(void)opt;
	return (0);
}

int main(int argc, char **argv)
{
	t_data		*data;
	t_options	opt;

	if (!checks(&opt, argc, argv)) // поставил "!", иначе ломалось
		return (1);
	if (opt.server)
		return (network(&opt));
	if ((data = compile(argv[1])) == NULL)
		return (1);
	if (make_file(data, argv[1]) == 0)
	{
		free_data(data);
		return (1);
	}
	free_data(data);
	return (0);
}
