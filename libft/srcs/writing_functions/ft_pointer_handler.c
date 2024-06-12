/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:02:07 by vsozonof          #+#    #+#             */
/*   Updated: 2023/03/09 21:24:23 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_pointer_converter(void *p)
{
	uintptr_t	ptr;

	ptr = (uintptr_t)p;
	if (ptr == 0)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	ft_putnbr_hexa(ptr, "0123456789abcdef");
}
