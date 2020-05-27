/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:51:45 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:51:48 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int ac, char **av)
{
    if (ac == 1)
        ft_putstr(USAGE);
    else if (ac > 2)
        ft_putstr_fd(ERROR_MANY_ARGS,2);
    else if (ac == 2 && check_file_name(av[1]))
        compile(av[1]);
    else
        ft_putstr_fd(ERROR_INVALID_CHAMP_NAME,2);
    return (0);
}
