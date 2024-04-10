/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:41:53 by ertupop           #+#    #+#             */
/*   Updated: 2023/11/01 12:07:49 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit_4(char **tab, t_list *gc)
{
	int		result;

	ft_exit2(tab, gc);
	if (ft_size_tab(tab) > 2)
	{
		ft_putstr_fd("exit\nminishell: exit : too many arguments\n", 1);
		return (1);
	}
	result = ft_exit3(tab);
	gc_dell(gc);
	ft_putstr_fd("exit\n", 1);
	exit(result);
}

int	ft_exit(char **tab, t_list *gc)
{
	int		i;

	i = -1;
	if (tab == NULL || ft_size_tab(tab) == 1)
	{
		gc_dell(gc);
		ft_putstr_fd("exit\n", 1);
		exit(g_exit);
	}
	if (tab[1][0] == '+' || tab[1][0] == '-')
		i++;
	while (tab[1][++i])
	{
		if (tab[1][i] < '0' || tab[1][i] > '9')
		{
			ft_exit5(tab);
			exit(2);
		}
	}
	return (ft_exit_4(tab, gc));
}

long long	ft_exit3(char **tab)
{
	long long	a;

	a = ft_atol(tab[1]);
	if (a > 255)
	{
		while (a > 255)
			a = a % 256;
	}
	return (a);
}

void	ft_exit2(char **tab, t_list *gc)
{
	if (ft_check_number(tab[1], gc) == 1)
	{
		ft_putstr_fd(tab[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		gc_dell(gc);
		ft_putstr_fd("exit\n", 1);
		exit(g_exit);
	}
}

int	ft_check_number(char *number, t_list *gc)
{
	long long	a;

	a = 9223372036854775807;
	if (ft_strlen("9223372036854775807") < ft_strlen(number))
		return (1);
	if (atol(number) > a)
	{
		ft_putstr_fd("exit : ", 1);
		ft_putstr_fd(number, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		gc_dell(gc);
		ft_putstr_fd("exit\n", 1);
		exit(2);
	}
	return (0);
}
