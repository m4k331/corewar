/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorphan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:47:33 by dorphan           #+#    #+#             */
/*   Updated: 2020/05/27 17:47:36 by dorphan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

int			opening_error_2(char *filename)
{
	ft_putstr_fd(ERROR_OPENING_FAILED, 2);
	ft_putstr_fd(filename, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int			no_end_of_line(t_data *data)
{
	ft_putstr_fd(ERROR_NO_END_OF_LINE, 2);
	close(data->fd);
	return (0);
}

int			check_buf(t_data *data, const char *buf, int ret)
{
	if (buf[ret] == '\n')
		return (1);
	if (ft_strcmp(data->current_token->type, "ENDLINE"))
		return (0);
	while (buf[ret - 1] != '\n')
		ret--;
	while (buf[ret])
	{
		if (buf[ret] != ' ' && buf[ret] != '\t'
				&& buf[ret] != COMMENT_CHAR && buf[ret] != ALT_COMMENT_CHAR)
			return (0);
		if (buf[ret] == COMMENT_CHAR || buf[ret] == ALT_COMMENT_CHAR)
			break ;
		ret++;
	}
	return (1);
}

int			check_last_end(t_data *data, char *filename)
{
	char	buf[1001];
	int		ret;
	char	last_char;

	ret = 0;
	last_char = '\0';
	if ((data->fd = open(filename, O_RDONLY)) == -1)
		return (opening_error_2(filename));
	while ((ret = read(data->fd, buf, 1000)))
	{
		buf[ret] = '\0';
		if (ft_strlen(buf) < 1000 && !check_buf(data, buf, ret - 1))
			return (no_end_of_line(data));
		last_char = buf[ret - 1];
	}
	if (ret == 0 && last_char != '\n'
			&& ft_strcmp(data->current_token->type, "ENDLINE"))
		return (no_end_of_line(data));
	init_token(data, "(null)", 13, 6);
	close(data->fd);
	return (1);
}
