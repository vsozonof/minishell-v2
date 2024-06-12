/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:15:16 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/04 07:44:15 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(t_env **env, char **tab)
{
	int		i;
	t_env	*tmp;

	i = 1;
	while (tab[i])
	{
		tmp = *env;
		while (tmp->next && ft_unset_cmp(tmp->var, tab[i]) != 0)
			tmp = tmp->next;
		if (ft_unset_cmp(tmp->var, tab[i]) == 0 && tmp != NULL)
			ft_unset_remove(tmp, env);
		i++;
	}
	return (0);
}

int	ft_unset_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s2[i] != '\0' || (s1[i] != '\0' && s1[i] != '='))
		return (1);
	return (0);
}

void	ft_unset_remove(t_env	*tmp, t_env **env)
{
	t_env	*last;
	t_env	*next;

	next = tmp->next;
	last = *env;
	if (tmp == *env)
	{
		(*env) = (*env)->next;
		free(tmp->var);
		free(tmp);
		return ;
	}
	while (last->next && tmp->var && ft_strcmp(tmp->var, last->next->var))
		last = last->next;
	free(tmp->var);
	free(tmp);
	last->next = next;
}
