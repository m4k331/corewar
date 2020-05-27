/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:47:14 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:47:18 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_file_name(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (filename[len - 1] == 's' && filename[len - 2] == '.')
		return (1);
	return (0);
}
