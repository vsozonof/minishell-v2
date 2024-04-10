/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_overflow_checker.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:44:02 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/13 11:03:24 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//------------------------------------------------------------------------------
//						--- Int Overflow Handler ---
//------------------------------------------------------------------------------

// This function takes a string that is supposed to be converted
// into an integer.

// In order to convert the string to an integer, we need to make sure
// no integer overflow wil occur while doing the conversion.

// Step 1 : Check the len of the string and see if it's above INT_MIN's len.
// Step 2 : Convert the string to long (A to L) and compare the integer
// with both INT_MIN and INT_MAX

// If the argument failed one of the steps, an error will be returned.

//------------------------------------------------------------------------------

long long int	ft_atoll_2(const char *str)
{
	long long int	var;
	int				i;
	int				sign;

	i = 0;
	sign = 1;
	var = 0;
	if (!(str))
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		var = (var * 10) + (str[i] - '0');
		i++;
	}
	return (var * sign);
}

int	ft_int_overflow_checker(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[0] == '+' || str[0] == '-')
		i--;
	if (i > 19)
		return (0);
	else if (ft_integer_checker(str) != 1)
		return (0);
	return (1);
}

int	ft_integer_checker(char *str)
{
	long long int	n;

	n = ft_atoll_2(str);
	if (n > LLONG_MAX)
		return (0);
	else if (n < LLONG_MIN)
		return (0);
	return (1);
}
