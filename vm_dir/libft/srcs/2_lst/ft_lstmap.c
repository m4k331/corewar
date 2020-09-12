/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:00:22 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

static void		clear_all(t_list **lst)
{
	t_list *hd;
	t_list *tmp;

	hd = *lst;
	while (hd != NULL)
	{
		tmp = hd;
		hd = hd->next;
		free(tmp->content);
		tmp->content_size = 0;
		free(tmp);
	}
	free(*lst);
	*lst = NULL;
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;
	t_list	*new;
	t_list	*tail;
	t_list	*head;

	if (!lst || !f)
		return (NULL);
	head = f(lst);
	node = lst->next;
	tail = head;
	while (node)
	{
		if (!(new = f(node)))
		{
			clear_all(&head);
			return (NULL);
		}
		tail->next = new;
		tail = new;
		node = node->next;
	}
	return (head);
}
