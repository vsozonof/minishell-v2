/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils-1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 05:50:43 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/28 01:04:35 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(t_env *env, char *str)
{
	int		len;
	t_env	*nav;
	char	*to_find;

	nav = env;
	to_find = ft_strjoin(str, "=");
	len = ft_strlen(to_find);
	while (nav)
	{
		if (!ft_strncmp(nav->var, to_find, len))
			return (free(to_find),
				ft_substr(nav->var, (len), ft_strlen(nav->var)));
		else
			nav = nav->next;
	}
	free(to_find);
	return (NULL);
}

t_env	*ft_get_env_node(t_env *env, char *str)
{
	int		len;
	t_env	*nav;

	nav = env;
	len = ft_strlen(str);
	while (nav)
	{
		if (!ft_strncmp(nav->var, str, len))
			return (nav);
		else
			nav = nav->next;
	}
	return (NULL);
}

int	put_env_to_lst(t_env *env, char **envp)
{
	int		i;
	t_env	*nav;

	i = 0;
	if (!envp)
		return (0);
	nav = env;
	while (envp[i])
	{
		nav->var = ft_strdup(envp[i]);
		if (!nav->var)
			return (0);
		if (envp[i + 1])
		{
			nav->next = malloc(sizeof(t_env));
			if (!nav->next)
				return (0);
			nav = nav->next;
		}
		else
			nav->next = NULL;
		i++;
	}
	return (1);
}
