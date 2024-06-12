/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:28:53 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 20:38:47 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_a	*ft_free_at_a(t_list_a *L, int pos)
{
	t_list_a	*prec;
	t_list_a	*cur;
	int			i;

	cur = L;
	prec = L;
	i = 0;
	if (pos == 0)
	{
		L = L->next;
		free(cur);
		return (NULL);
	}
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cur->next;
	free(cur);
	return (L);
}

t_list_b	*ft_free_at_b(t_list_b *L, int pos)
{
	t_list_b	*prec;
	t_list_b	*cur;
	int			i;

	cur = L;
	prec = L;
	i = 0;
	if (pos == 0)
	{
		L = L->next;
		free(cur);
		return (NULL);
	}
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cur->next;
	free(cur);
	return (L);
}
