/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <dorphan@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:46:28 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:46:40 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** Usage
*/

# define USAGE "Usage: ./asm champion_name.s\n"


/*
** ERRORS
*/

# define ERROR_MANY_ARGS "Too many arguments.\n"
# define ERROR_INVALID_CHAMP_NAME "Invalid champion name.\n"
# define ERROR_OPENING_FAILED "Can't open file: "
# define ERROR_MEMORY_ALLOCATION "Memory allocation failed.\n"
# define ERROR_READ_FILE "Can't read source file "
# define ERROR_LONG_NAME "Champion name too long (Max length 128)\n"
# define ERROR_LONG_COMMENT "Champion comment too long (Max length 2048)\n"
# define ERROR_LEXICAL "Lexical error at "
# define ERROR_SYNTAX "Syntax error at token [TOKEN]"
# define ERROR_NO_END_OF_LINE "Syntax error - unexpected end of input (Perhaps you forgot to end with a newline?)\n"
# define ERROR_INVALID_INSTRUCTION "Invalid instruction at token [TOKEN]"
# define ERROR_INVALID_ARG "Invalid parameter "
# define ERROR_INVALID_ARGS_COUNT "Invalid parameter count for instruction "
# define ERROR_NO_LABEL "No such label "


/*
** Types of tokens
*/

# define ENDLINE 0
# define NAME 1
# define NAME_COMMENT 2
# define STRING 3
# define COMMENT 4
# define LABEL 5


# include "libft/includes/libft.h"
# include "op.h"


/*
** tokens list
*/

typedef struct		s_token
{
	char			*type;
	char			*content;
	int				is_finished;
	int				line_num;
	int				char_num;
	unsigned char	op_code;
	unsigned char	args_code;
	int				args_size;
	int				t_dir_size;
	int				byte_number;
	int				byte_size;
	struct s_token	*args;
	struct s_token	*next;
}					t_token;


/*
** main data structure
*/

typedef struct		s_data
{
	int				fd;
	int				line_num;
	int				char_num;
	unsigned char	*buffer;
	int				buffer_len_iter;
	int				current_byte;
	int				buffer_len;
	t_token			*name;
	t_token			*comment;
	t_token			*current_token;
	t_token			*token;
}					t_data;

/*
** error.c
*/
int					error(t_data *data);
int					error_instruction(t_data *data);
int					error_invalid_arg(t_data *data, t_token *arg, int num);
int					error_args_count(t_data *data);
int					error_no_label(t_data *data, t_token *arg, char *c);

/*
** check_file_name.c
*/
int					check_file_name(char *filename);

/*
** assembler.c
*/
int					compile(char *filename);

/*
** initialization.c
*/
int					increase_buffer(t_data *data);
int					init_buffer(t_data *data);
t_token				*init_token(t_data *data, char *line, int type, int len);
t_data				*init_data(void);

/*
** lexer.c
*/
int					lexer(t_data *data, char *filename);

/*
** check_last_end.c
*/
int 				check_last_end(t_data *data, char *filename);

/*
** memory_cleaning.c
*/
void				free_data(t_data *data);


/*
** is_name_or_comment.c
*/
int					is_name_or_comment(t_data *data, char *line);


/*
** is_string.c
*/
int					get_continue_of_string(t_data *data, char *line);
int					is_string(t_data *data, char *line);


/*
** is_comment.c
*/
int					is_comment(t_data *data, char *line);

/*
** is_separator.c
*/
int					is_separator(t_data *data, char *line);

/*
** is_label_char.c
*/
int					is_lonely_label_char(t_data *data);
int 				is_label_char(t_data *data, char *line);


/*
** is_direct.c
*/
int					is_direct(t_data *data, char *line);


/*
** is_num.c
*/
int					is_num(t_data *data, char *line);

/*
** is_label_instr_reg_ind.c
*/
int					lex_error_label(t_data *data, int i);
int					is_label_instr_reg(t_data *data, char *line);

/*
** make_tree.c
*/
int					make_tree(t_data *data);

/*
** parse_token.c
*/
void				delete_token(t_data *data);
int					parse_token(t_data *data);

/*
** parse_name_and_comment.c
*/
int					parse_name_and_comment(t_data *data, int calc);

/*
** parse_instruction.c
*/
int					parse_instruction(t_data *data);

/*
** parse_tree.c
*/
int					parse_tree(t_data *data);

/*
** instructions_1.c
*/
int					op_live_zjmp_fork_lfork(t_data *data);
int					op_ld_lld(t_data *data);
int					op_st(t_data *data);
int					op_add_sub(t_data *data);
int					op_and_or_xor(t_data *data);


/*
** instructions_2.c
*/
int					op_ldi_lldi(t_data *data);
int					op_sti(t_data *data);
int					op_aff(t_data *data);

/*
** make_hex_buffer.c
*/
int					make_hex_buffer(t_data *data);


/*
** put_commands.c
*/
int					put_commands(t_data *data, int *current_pos);

/*
** calc_sizes.c
*/
void				calc_sizes(t_data *data);

/*
** get_op_weight.c
*/
void				get_op_weight(t_data *data, unsigned char op_code, int t_dir_size, unsigned char args_code);

/*
** make_file.c.c
*/
int					make_file(t_data *data, char *filename);

#endif
