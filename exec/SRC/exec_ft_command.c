/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ft_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostrub <rostrub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:54:41 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/14 11:21:14 by rostrub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_check_command(int fd, char *command, t_data **data)
{
	fd = open(command, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_fprintf(2, "minishell : ");
		ft_printf("%s: Is a Directory\n", command);
		free_end_of_program((*data)->pr);
		free_master(*data);
		exit(126);
	}
	else
		return (command);
}

char	*ft_command2(t_pipex *pip, char *command, t_env **env, int i)
{
	char	*tmp;
	int		fd;

	ft_path(env, pip);
	if (pip->path == NULL)
		return (NULL);
	while (pip->path[++i])
	{
		tmp = ft_join(pip->path[i], command);
		if (access(tmp, X_OK) == 0)
		{
			fd = open(tmp, __O_DIRECTORY);
			if (fd == -1)
				return (tmp);
			close(fd);
		}
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

void	ft_free_path(t_pipex *pip)
{
	int	i;

	i = 0;
	if (pip->path != NULL)
	{
		while (pip->path[i])
		{
			free(pip->path[i]);
			i++;
		}
		free(pip->path);
	}
}
