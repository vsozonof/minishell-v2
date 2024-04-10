/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:28:32 by vsozonof          #+#    #+#             */
/*   Updated: 2023/10/03 12:35:37 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_at_a(t_list_a *L, int pos)
{
	int	i;

	i = 0;
	if (L == NULL)
		return (0);
	while (i < pos && L->next)
	{
		i++;
		L = L->next;
	}
	return (L->data);
}

int	ft_get_at_b(t_list_b *L, int pos)
{
	int	i;

	i = 0;
	if (L == NULL)
		return (0);
	while (i < pos)
	{
		i++;
		L = L->next;
	}
	return (L->data);
}
