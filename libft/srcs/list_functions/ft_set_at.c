/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:53:30 by vsozonof          #+#    #+#             */
/*   Updated: 2023/10/03 12:35:18 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_at_a(t_list_a *L, int data, int pos)
{
	int	i;

	i = 0;
	if (L == NULL)
		return ;
	while (i < pos)
	{
		i++;
		L = L->next;
	}
	L->data = data;
}

void	ft_set_at_b(t_list_b *L, int data, int pos)
{
	int	i;

	i = 0;
	if (L == NULL)
		return ;
	while (i < pos)
	{
		i++;
		L = L->next;
	}
	L->data = data;
}
