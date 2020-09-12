/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_input_parse_champ.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:00:47 by limry             #+#    #+#             */
/*   Updated: 2020/09/08 18:41:46 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_game_input.h"
#include "op.h"

int					vm_parse_byte_to_32int(uint32_t *data, int size)
{
	int				res;
	uint8_t			sign;
	int				i;

	sign = *data & 0x80;
	res = 0;
	i = -1;
	while (++i < size)
		if (sign)
			res |= ((*data >> (i * 8)) ^ 0xFF) << ((3 - i) * 8);
		else
			res |= ((*data >> (i * 8)) & 0xFF) << ((3 - i) * 8);
	if (sign)
	{
		res |= 0x80000000;
		res = res + 1;
	}
	return (res);
}

int					vm_input_parse_champ_offline(int fd, t_champ *champ,
					t_input *input)
{
	uint8_t			buf[CHAMP_MAX_SIZE];
	t_header_new	head;

	ft_bzero(buf, CHAMP_MAX_SIZE);
	if ((int)sizeof(t_header_new) > read(fd, &head, sizeof(t_header_new)))
		vm_error("Error: champ file has too short header. OUI", input);
	else if (vm_parse_byte_to_32int(&head.magic, 4) != COREWAR_EXEC_MAGIC)
		vm_error("Error: champ file has wrong magic header", input);
	else if (head.null_name != 0)
		vm_error("Error: wrong champ file - no null after name", input);
	else
		ft_memcpy(champ->name, head.prog_name, PROG_NAME_LENGTH);
	if (CHAMP_MAX_SIZE < (champ->code_size =
			vm_parse_byte_to_32int(&head.prog_size, 4)))
		vm_error("Error: wrong champ file - code size is too big", input);
	if (head.null_comment != 0)
		vm_error("Error: wrong champ file - no null after comment", input);
	else
		ft_memcpy(champ->comment, head.comment, COMMENT_LENGTH);
	if (champ->code_size > read(fd, buf, champ->code_size))
		vm_error("Error: wrong champ file - not enough of code", input);
	else
		ft_memcpy(champ->code, buf, champ->code_size);
	read(fd, buf, 1) ? vm_error("Error: champ code is fat", input) : 1;
	return (0);
}

int					vm_input_parse_champ_online(t_champ *champ,
					uint8_t *raw_data, int err_fd)
{
	t_header_new	*head;
	int				r;

	head = (t_header_new*)raw_data;
	if ((r = vm_parse_byte_to_32int(&(head->magic), 4)) != COREWAR_EXEC_MAGIC)
		return (vm_nofity_err(err_fd,
			ERR_PARSE_MSG_WRONG_MAGIC, CODE_ERR_PARSE_MSG_WRONG_MAGIC));
	else if (head->null_name != 0)
		return (vm_nofity_err(err_fd,
			ERR_PARSE_MSG_NO_NULL_NAME, CODE_ERR_PARSE_MSG_NO_NULL_NAME));
	else
		ft_memcpy(champ->name, head->prog_name, PROG_NAME_LENGTH);
	if (CHAMP_MAX_SIZE < (champ->code_size =
			vm_parse_byte_to_32int(&(head->prog_size), 4)))
		return (vm_nofity_err(err_fd, ERR_PRS_BIG_SIZE, CD_ERR_PRS_BIG_SIZE));
	if (head->null_comment != 0)
		return (vm_nofity_err(err_fd,
			ERR_PARSE_MSG_NO_NULL_COM, CODE_ERR_PARSE_MSG_NO_NULL_COM));
	else
		ft_memcpy(champ->comment, head->comment, COMMENT_LENGTH);
	ft_memcpy(champ->code, raw_data + sizeof(t_header_new), champ->code_size);
	return (0);
}
