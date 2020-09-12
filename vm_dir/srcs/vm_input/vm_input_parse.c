/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:00:53 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:00:53 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

static int		vm_get_free_index_in_names(t_input *input)
{
	int			i;

	i = 0;
	while (input->champ_files[i] != NULL && i < MAX_PLAYERS)
		i++;
	if (i > 3)
		vm_error("Too many champions!", input);
	return (i);
}

static int		vm_set_name_of_champ_for_offline(t_input *input,
				int av_index, int to_parse_n)
{
	uint64_t	n;
	int			free_index;

	free_index = vm_get_free_index_in_names(input);
	if (to_parse_n)
	{
		if (av_index >= input->ac)
			vm_error("No arguments after n flag", input);
		n = ft_atoli(input->av[av_index]);
		if (n > MAX_PLAYERS || n < 1)
			vm_error("Error: set index of player between 1 and 4", input);
		if (input->champ_files[n - 1] != NULL)
			input->champ_files[free_index] = input->champ_files[n - 1];
		if (av_index + 1 >= input->ac)
			vm_error("No arguments after position definition", input);
		input->champ_files[n - 1] = input->av[av_index + 1];
	}
	else if (av_index >= input->ac)
		vm_error("Wrong argument of champ file", input);
	else
		input->champ_files[free_index] = input->av[av_index];
	return (1);
}

static int		vm_parse_flag(char *flag)
{
	if (!ft_strcmp(flag, "-dump"))
		return (5);
	if (!ft_strcmp(flag, "-n"))
		return (1);
	if (!ft_strcmp(flag, "--server") || !ft_strcmp(flag, "-s"))
		return (4);
	if (!ft_strcmp(flag, "--log") || !ft_strcmp(flag, "-l"))
		return (6);
	return (-1);
}

static void		vm_parse_flag_setting(int *av_index, t_input *input,
				int *flag_type, int *num_champs)
{
	if (*flag_type == 1)
	{
		*num_champs += 1;
		vm_set_name_of_champ_for_offline(input, ++(*(av_index)), 1);
		++(*(av_index));
	}
	else if (*flag_type == 4)
		input->flag_server = TRUE;
	else if (*flag_type == 5 && ++(*av_index) < input->ac)
		input->flag_dump = ft_atoli(input->av[*(av_index)]);
	else if (*flag_type == 6 && ++(*av_index) < input->ac)
		input->flag_log = ft_atoli(input->av[*(av_index)]);
	else if (*flag_type < 0)
		vm_error("Error: found irrelevant flag", input);
}

void			vm_input_define(t_input *input)
{
	int			flag_type;
	int			num_champs;
	int			av_index;

	av_index = 0;
	flag_type = 0;
	num_champs = 0;
	while (++av_index < input->ac)
	{
		if (input->av[av_index][0] == '-' &&
		(flag_type = vm_parse_flag(input->av[av_index])))
			vm_parse_flag_setting(&av_index, input, &flag_type, &num_champs);
		else if (++num_champs < MAX_PLAYERS + 1)
			vm_set_name_of_champ_for_offline(input, av_index, 0);
		else
			vm_error("Error: too many champions!", input);
	}
	vm_input_define_mode(input, num_champs);
}
