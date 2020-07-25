/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:51:45 by dorphan           #+#    #+#             */
/*   Updated: 2020/07/25 14:50:43 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "network.h"
#include <stdio.h> // TODO: remove

int		main_old(int ac, char **av)
{
	if (ac == 1)
		ft_putstr(USAGE);
	else if (ac > 2)
		ft_putstr_fd(ERROR_MANY_ARGS, 2);
	else if (check_file_name(av[1]))
		compile(av[1]);
	else
		ft_putstr_fd(ERROR_INVALID_CHAMP_NAME, 2);
	return (0);
}

int usage(int fd, char *prog_name)
{
	write(fd, USAGE_START, sizeof(USAGE_START));
	ft_putstr_fd(prog_name, fd);
	write(fd, USAGE_ARGS, sizeof(USAGE_ARGS));
	return (0);
}

int invalid_opt(char *opt)
{
	write(2, "Invalid option: \"", sizeof("Invalid option: \""));
	ft_putendl_fd(opt, 2);
	return (0);
}

int ft_is_number(char *str)
{
	int i;
	int dig_was_found;

	i = 0;
	while (ft_isspace(str[i]) && str[i])
		i++;
	dig_was_found = 0;
	while (ft_isdigit(str[i]) && str[i])
	{
		dig_was_found = 1;
		i++;
	}
	while (ft_isspace(str[i]) && str[i])
		i++;
	if (str[i] != '\0' || !dig_was_found)
		return (0);
	return (1);
}

int invalid_port_number(char *port)
{
	write(2, "Invalid port number: \"", sizeof("Invalid port number: \""));
	ft_putstr_fd(port, 2);
	write(2, "\"\n", 2);
	return (0);
}

int	get_options(t_options *opt, int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 2 && ft_strcmp(argv[1], "-h"))
		opt->filename = argv[++i];
	while (++i < argc)
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'h' && argv[i][2] == '\0')
				exit(usage(1, argv[0]));
			else if (i + 1 >= argc)
				return (1);
			if (argv[i][1] == 'i' && argv[i][2] == '\0')
				opt->ip = argv[i++ + 1];
			else if (argv[i][1] == 'p' && argv[i][2] == '\0')
			{
				if (!ft_is_number(argv[i + 1]))
					return (1 | invalid_port_number(argv[i + 1]));
				opt->port = ft_atoi(argv[i++ + 1]);
			}
			else
				return (1 | invalid_opt(argv[i]));
		}
		else
			return (1);
	return (0);
}

int checks(t_options *opt, int argc, char **argv)
{
	ft_memset(opt, 0, sizeof(t_options));
	if (get_options(opt, argc, argv))
		return (1);
	if (!opt->filename)
	{
		if (opt->ip == NULL)
			return (1);
		if (opt->port == 0)
			opt->port = DEFAULT_HUB_PORT;
	}
	else if (check_file_name(opt->filename) == 0)
	{
		ft_putstr_fd(ERROR_INVALID_CHAMP_NAME, 2);
		return (1);
	}
	return (0);
}

// TODO: remove
int print_opt(t_options *opt)
{
	printf("IP: %s\n", opt->ip);
	printf("Port: %hd\n", opt->port);
	printf("Filename: %s\n", opt->filename);
	return (0);
}

int main(int argc, char **argv)
{
	t_data		*data;
	t_options	opt;

	if (checks(&opt, argc, argv))
		return (1 | usage(2, argv[0]));
	// print_opt(&opt);
	// return (0);
	if (!opt.filename)
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
