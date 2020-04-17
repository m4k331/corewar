/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnarbo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 23:51:21 by rnarbo            #+#    #+#             */
/*   Updated: 2020/04/17 10:23:04 by rnarbo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define OPT_NB_MASK	0x1
# define OPT_MINUS_MASK	0x2
# define OPT_OB_MASK	0x4

# define TCP_QUEUE_SIZE	10

typedef struct s_options
{
	int		options;
	int		port;
	int		optimize_lvl;
}	t_options;

typedef enum
{
	CMD,
	OP,
	LBLI,
	LBLU,
	DIR,
	IND,
	REG,
	COM,
	SEP,
	STR
}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	void			*content;
	t_token			*next;
}				t_token; // TODO: fix structure t_token

typedef struct	s_token_stream
{
	t_token	*tokens;
	t_token	*token_p;
	int		tokens_size;
}				t_token_stream;

typedef struct s_ast {int i;} t_ast; // TODO: fix structure t_ast

#endif