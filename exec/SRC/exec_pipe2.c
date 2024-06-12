/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:00:09 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/10 10:00:52 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_pipe5(t_pipex *pip, t_env **env, t_cmd *tmp, t_data **data)
{
	pip->command = ft_command(pip, tmp->param[0], env, data);
	if (pip->command == NULL)
	{
		ft_fprintf(2, "minishell : ");
		ft_fprintf(2, "%s: command not found\n", tmp->param[0]);
		close(pip->pipe[0]);
		close(pip->pipe[1]);
		close(0);
		close(1);
		close(2);
		free_master(*data);
		exit(127);
	}
	ft_close_fd(pip->infile, pip->outfile);
	if (execve(pip->command, tmp->param, tmp->env) == -1)
	{
		free_master(*data);
		exit(1);
	}
}

int	ft_exec_pipebultins(t_cmd *tmp, t_env **env, int tokken, t_data **data)
{
	int	result;

	result = 0;
	if (tokken == CD)
		result = ft_cd(tmp->param, *env);
	else if (tokken == ECHO)
		result = ft_echo(tmp->param);
	else if (tokken == ENV)
		result = ft_print_env(*env);
	else if (tokken == EXIT)
		execute_exit(tmp->param, *data);
	else if (tokken == EXPORT)
		result = ft_export(tmp->param, env);
	else if (tokken == PWD)
		result = ft_pwd();
	else if (tokken == UNSET)
		result = ft_unset(env, tmp->param);
	free_master(*data);
	return (result);
}

void	ft_close_one(int s, int i)
{
	close(s);
	close(i);
}
