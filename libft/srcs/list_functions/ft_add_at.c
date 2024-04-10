/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:26:18 by vsozonof          #+#    #+#             */
/*   Updated: 2023/10/03 12:36:27 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_a	*ft_add_at_a(t_list_a *L, int data, int pos)
{
	t_list_a	*prec;
	t_list_a	*cur;
	t_list_a	*cell;
	int			i;

	cur = L;
	prec = L;
	i = 0;
	cell = ft_create_cell_a(data);
	if (L == NULL)
		return (cell);
	if (pos == 0)
	{
		cell->next = L;
		return (cell);
	}
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return (L);
}

t_list_b	*ft_add_at_b(t_list_b *L, int data, int pos)
{
	t_list_b	*prec;
	t_list_b	*cur;
	t_list_b	*cell;
	int			i;

	cur = L;
	prec = L;
	i = 0;
	cell = ft_create_cell_b(data);
	if (L == NULL)
		return (cell);
	if (pos == 0)
	{
		cell->next = L;
		return (cell);
	}
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return (L);
}
