/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exev_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:22:15 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/10 07:25:10 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_path(t_env **env, t_pipex *pip)
{
	t_env	*tmpo;
	int		len;
	char	*tmp;

	tmpo = NULL;
	tmpo = ft_get_env_pos(*env, "PATH");
	if (tmpo == NULL)
	{
		pip->path = NULL;
		return ;
	}
	len = ft_strlen(tmpo->var);
	tmp = malloc(sizeof(char) * ((len - 5) + 1));
	if (!tmp)
	{
		pip->path = NULL;
		return ;
	}
	ft_strlcpy(tmp, tmpo->var + 5, len + 1);
	pip->path = ft_split(tmp, ':');
	free(tmp);
}

char	*ft_command(t_pipex *pip, char *command, t_env **env, t_data **data)
{
	int		fd;
	char	*tmp;
	int		i;

	i = -1;
	fd = 0;
	tmp = NULL;
	if (command == NULL)
		return (NULL);
	if (ft_is_a_slash(command) == 1)
	{
		if (access(command, 0) == 0)
		{
			return (ft_check_command(fd, command, data));
		}
		else
			return (NULL);
	}
	tmp = ft_command2(pip, command, env, i);
	if (tmp != NULL)
		return (tmp);
	ft_free_path(pip);
	return (NULL);
}

int	ft_is_a_slash(char	*command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_join(char *first, char *second)
{
	char	*join;
	int		i;
	int		i2;

	i = -1;
	if (first == NULL || second == NULL)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(first) + ft_strlen(second) + 2));
	if (join == NULL)
		return (NULL);
	while (first[++i])
		join[i] = first[i];
	join[i] = '/';
	i2 = 0;
	i++;
	while (second[i2])
	{
		join[i] = second[i2];
		i++;
		i2++;
	}
	join[i] = '\0';
	return (join);
}
