/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bultins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 07:28:09 by ertupop           #+#    #+#             */
/*   Updated: 2024/05/27 12:56:53 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_find_env(t_env *env, char *find)
{
	int		i2;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		i2 = 0;
		while (tmp->var[i2] && tmp->var[i2] == find[i2] && find[i2])
			i2++;
		if (find[i2] == '\0' && tmp->var[i2 - 1] == '=')
			return (tmp->var);
		else
			tmp = tmp->next;
	}
	return (NULL);
}
