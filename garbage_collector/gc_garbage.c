/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 07:23:18 by ertupop           #+#    #+#             */
/*   Updated: 2024/05/27 11:35:31 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	gc_malloc(t_lst *garbage, void	*ptr)
{
	t_lst	*new;

	if (ptr == NULL)
		return (1);
	new = ft_lstnew(ptr);
	ft_lstadd_back(&garbage, new);
	return (0);
}

void	gc_dell(t_lst *garbage)
{
	ft_lstclear(&garbage, free);
}

int	gc_dell_one(t_lst *garbage, void *ptr)
{
	t_lst	*prec;
	t_lst	*next;
	t_lst	*tmp;

	tmp = garbage;
	while (tmp != NULL && tmp->content != ptr)
	{
		prec = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (1);
	next = tmp->next;
	ft_lstdelone(tmp, free);
	prec->next = next;
	return (0);
}
