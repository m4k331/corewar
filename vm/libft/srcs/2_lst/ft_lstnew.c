/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:00:26 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*result;

	if (!(result = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		result->content = NULL;
		result->content_size = 0;
	}
	else
	{
		if (!(result->content = malloc(sizeof(*(result->content))\
										* content_size)))
		{
			free(result);
			return (NULL);
		}
		result->content = ft_memcpy(result->content, content, content_size);
		result->content_size = content_size;
	}
	result->next = NULL;
	return (result);
}
