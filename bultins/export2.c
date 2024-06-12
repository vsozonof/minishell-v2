/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 08:20:29 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/04 07:37:52 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_check_export(char *str)
{
	int	i2;

	if ((str[0] < 'a' || str[0] > 'z') && (str[0] < 'A'
			|| str[0] > 'Z') && str[0] != '_')
	{
		write(2, "minishell : export: ", 20);
		ft_putstr_fd(str, 2);
		write(2, " : not a valid identifier\n", 26);
		return (1);
	}
	i2 = 1;
	while (str[i2] && str[i2] != '=')
	{
		if ((str[i2] < 'a' || str[i2] > 'z') && (str[i2] < 'A'
				|| str[i2] > 'Z') && str[i2] != '_' && (str[i2] < '0'
				|| str[i2] > '9') && (str[i2] != '+' && str[i2 + 1] != '='))
		{
			write(2, "minishell : export: ", 20);
			ft_putstr_fd(str, 2);
			write(2, " : not a valid identifier\n", 26);
			return (1);
		}
		i2++;
	}
	return (0);
}

void	ft_join_export(char *str, t_env *tmp)
{
	char	*tmpo;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	tmpo = ft_strdup(tmp->var);
	free(tmp->var);
	tmp->var = ft_strjoin(tmpo, str + i);
	free(tmpo);
}
