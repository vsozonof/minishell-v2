/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:30:33 by firawar           #+#    #+#             */
/*   Updated: 2024/07/01 15:58:00 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	i = 0;
	while (s2[i])
		i++;
	str = malloc(sizeof(char) * (len + i + 1));
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	len = -1;
	while (s2[++len])
		str[i + len] = s2[len];
	str[i + len] = '\0';
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_cd_update(char *tmpo, t_env *env, t_env *tmp)
{
	t_env	*old;

	old = ft_get_env_pos(env, "OLDPWD");
	if (old == NULL)
		ft_add_oldpwd(tmp->var + 4, env);
	else
	{
		free(old->var);
		old->var = ft_strjoin("OLDPWD=", tmp->var + 4);
	}
	free(tmp->var);
	tmp->var = ft_strjoin("PWD=", tmpo);
}
