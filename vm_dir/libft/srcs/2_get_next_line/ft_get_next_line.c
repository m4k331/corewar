/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:27:07 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_lst		*ft_get_or_add(t_lst *hd, int fd)
{
	t_lst			*new;
	t_lst			*lst;
	t_lst			*last;

	lst = hd;
	while (lst)
	{
		if (lst->dn == fd)
			return (lst);
		if (!lst->next)
			last = lst;
		lst = lst->next;
	}
	if ((new = (t_lst*)malloc(sizeof(t_lst))))
	{
		new->dn = fd;
		new->next = NULL;
		new->rot = 0;
		new->nl = NULL;
		new->str = dstr_init(NULL, BUFF_SIZE << 2);
		if (hd && last)
			last->next = new;
		return (new);
	}
	return (NULL);
}

static void			ft_del_fd(t_lst *lst, t_lst *hd)
{
	t_lst			*tmp;

	tmp = hd;
	if (hd == lst)
	{
		dstr_del(lst->str);
		lst->next = NULL;
		free(lst);
		lst = NULL;
		return ;
	}
	while (tmp != lst && tmp->next != lst && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->next == lst)
	{
		tmp->next = tmp->next->next;
		dstr_del(lst->str);
		free(lst);
		lst->next = NULL;
	}
}

static int			read_file(t_lst *lst, const int fd)
{
	char			buf[BUFF_SIZE + 1];
	long int		ret;

	lst->rot = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		dstr_joinstr(lst->str, buf);
		if ((lst->nl = ft_strchr(lst->str->start + lst->rot, '\n')))
			break ;
		lst->rot += BUFF_SIZE;
	}
	return (ret);
}

static int			show_line(t_lst *lst, char **line)
{
	char			*nl;

	if ((nl = ft_strchr(lst->str->start + lst->rot, '\n')))
	{
		dstr_pop_front(lst->str, line, nl - lst->str->start);
		dstr_pop_front(lst->str, NULL, 1);
		lst->rot = 0;
		return (1);
	}
	dstr_pop_front(lst->str, line, lst->str->cap);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_lst	*hd;
	t_lst			*lst;
	t_lst			*hd1;
	long int		ret;

	if (fd < 0)
		return (clean_all_gnl(hd));
	if (!line || BUFF_SIZE <= 0)
		return (-1);
	if (!hd)
		hd = ft_get_or_add(hd, fd);
	lst = ft_get_or_add(hd, fd);
	ret = read_file(lst, fd);
	if (ret < 0)
		return (-1);
	if (!(lst->str->len_data) && !ret)
	{
		hd1 = hd;
		if (lst == hd)
			hd = hd->next;
		ft_del_fd(lst, hd1);
		return (0);
	}
	return (show_line(lst, line));
}
