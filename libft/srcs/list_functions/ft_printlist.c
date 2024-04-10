/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:26:44 by vsozonof          #+#    #+#             */
/*   Updated: 2023/10/03 12:35:20 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printlst_a(t_list_a *L)
{
	if (L == NULL)
	{
		printf("La liste est vide.\n");
		return ;
	}
	ft_printf("LISTE A = \n");
	while (L)
	{
		ft_printf("[%d][%d] -> %d\n", L->pos, L->index, L->data);
		L = L->next;
	}
}

void	ft_printlst_b(t_list_b *L)
{
	if (L == NULL)
	{
		printf("La liste est vide.\n");
		return ;
	}
	ft_printf("LISTE B = \n");
	while (L)
	{
		ft_printf("[%d]%d\n", L->index, L->data);
		L = L->next;
	}
	ft_printf("\n");
}
