/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_prev_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:12:51 by vsozonof          #+#    #+#             */
/*   Updated: 2023/10/03 12:35:28 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_add_prev_ptr_a(t_list *stacks)
{
	t_list_a	*ptr;
	t_list_a	*tmp;

	tmp = NULL;
	ptr = stacks->a;
	while (ptr)
	{
		ptr->prev = tmp;
		tmp = ptr;
		ptr = ptr->next;
	}
}

void	ft_add_prev_ptr_b(t_list *stacks)
{
	t_list_b	*ptr;
	t_list_b	*tmp;

	tmp = NULL;
	ptr = stacks->b;
	while (ptr)
	{
		ptr->prev = tmp;
		tmp = ptr;
		ptr = ptr->next;
	}
}
