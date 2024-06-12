/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:41:53 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/10 09:56:45 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long long int	ft_atoll_1(const char *str)
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

int	status_checker(char	*status, t_data *data)
{
	long int	i_status;
	int			i;

	i = -1;
	if (status[0] == '-' || status[0] == '+')
		i++;
	while (status[++i])
		if (!ft_isdigit(status[i]))
			return (set_status(data, 2,
					"numeric argument required", "exit"), 2);
	if (!ft_int_overflow_checker(status))
		return (set_status(data, 2,
				"numeric argument required", "exit"), 2);
	i_status = ft_atoll_1(status);
	if (i_status < 0 || i_status > 255)
		i_status = (i_status % 256 + 256) % 256;
	return (i_status);
}

void	execute_exit(char **param, t_data *data)
{
	int	status;

	printf("exit\n");
	if ((get_dtab_len(param) - 1) == 0)
		data->exited = 1;
	else if ((get_dtab_len(param) - 1) == 1)
	{
		status = status_checker(param[1], data);
		set_status(data, status, NULL, NULL);
		data->exited = 1;
	}
	else
	{
		set_status(data, 1, "too many arguments", "exit");
		data->exited = 1;
	}
}
