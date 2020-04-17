/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 11:17:40 by rnarbo            #+#    #+#             */
/*   Updated: 2020/04/17 10:39:00 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stddef.h>

int compile(char **compilled, char *buffer)
{
	t_token_stream	*stream;
	t_ast			*ast;
	int				comp_len;
	int				status;
	
	if ((stream = scanner(buffer)) == NULL)
		return (-1);
	ast = parser(stream);
	destroy_stream(stream);
	if (ast == NULL)
		return (-1);
	status = semantic_analyzer(ast);
	if (status < 0)
	{
		destroy_ast(ast);
		return (-1);
	}
	if ((comp_len = tree2asm(compilled, ast)))
		return (-1);
	destroy_ast(ast);
	return (comp_len);
}