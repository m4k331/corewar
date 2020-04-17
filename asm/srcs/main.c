/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 12:17:47 by rnarbo            #+#    #+#             */
/*   Updated: 2020/03/23 22:10:43 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

#define ft_memset memset
#define ft_isdigit isdigit

void	parse_options(t_options *options, int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	ft_memset(options, 0, sizeof(options));
	while (i < argc && argv[i][0] == '-') // TODO: handle dup options
	{
		j = 0;
		if (argv[i][1] == 'h' && argv[i][2] == '\0')
			exit(usage(argv[0]) & 0);
		else if (argv[i][1] == 'N' && argv[i][2] == '\0')
		{
			options->options |= OPT_NB_MASK;
			if (i + 1 < argc)
				options->port = ft_atoi(argv[i + 1]); // TODO: Check
			i++;
		} else if (argv[i][1] == '-' && argv[i][2] == '\0')
		{
			i++;
			break;
		} else if (argv[i][1] == 'O' && ft_isdigit(argv[i][2]) && argv[i][3] == '\0')
		{
			options->options |= OPT_OB_MASK;
			options->optimize_lvl = argv[i][2] - '0';
		} else
		{
			ft_putstr_fd("Error: Invalid option: \"", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("\"\n", 2);
			exit(usage(argv[0]));
		}
		i++;
	}
	if (i != argc - 1 && (options->options & OPT_NB_MASK) == 0)
		exit(usage(argv[0])); // TODO:
}

int	main(int argc, char **argv)
{
	t_options	opt;
	char		*compiled;
	int			comp_len;
	char		*buffer;
	
	parse_options(&opt, argc, argv);
	if (opt.options & OPT_NB_MASK)
		network(opt); // TODO:
	buffer = get_buffer_form_file(argv[argc - 1]);
	if ((comp_len = compile(&compiled, buffer)) < 0) // TODO:
		return (-1); // TODO: error handle
	if (write_champion(argv[argc - 1], compiled, comp_len) < 0) // TODO:
	{
		free(compiled);
		return (-1);
	}
	free(compiled);
	return (0);
}