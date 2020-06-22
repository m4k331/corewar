/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:47:14 by dorphan           #+#    #+#             */
/*   Updated: 2020/06/21 18:13:51 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_file_name(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	// FIXME: тут получается, что идет обращение к len - 1 и len - 2,
	//        но чисто технически len может быть 0
	// FIXED
	if (len && filename[len - 1] == 's' && filename[len - 2] == '.')
		return (1);
	return (0);
}
