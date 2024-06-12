/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:27:14 by vsozonof          #+#    #+#             */
/*   Updated: 2023/10/03 12:35:42 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_lstlen_a(t_list_a *L)
{
	long	len;

	len = 0;
	while (L)
	{
		len++;
		L = L->next;
	}
	return (len);
}

long	ft_lstlen_b(t_list_b *L)
{
	long	len;

	len = 0;
	while (L)
	{
		len++;
		L = L->next;
	}
	return (len);
}
