/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 07:37:59 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/12 16:47:10 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_one(t_cmd *cmd, t_env **env, t_pipex *pip, t_data **data)
{
	t_exec	exec;

	if (cmd->param[0] == NULL)
		return (0);
	exec.tokken = ft_exec_openfd(&cmd, &cmd->redirs, &pip);
	pip->out = dup(1);
	pip->in = dup(0);
	dup2(pip->infile, 0);
	dup2(pip->outfile, 1);
	if (exec.tokken == EXIT)
		ft_close_one(pip->out, pip->in);
	if (exec.tokken == NO)
		exec.result = ft_execve_one(env, pip, cmd, data);
	else if (exec.tokken != NO)
		exec.result = ft_exec_bultins(cmd, env, exec.tokken, data);
	dup2(pip->out, 1);
	dup2(pip->in, 0);
	close(pip->out);
	close(pip->in);
	return (exec.result);
}

int	ft_execve_one(t_env **env, t_pipex *pip, t_cmd *tmp, t_data **data)
{
	int		result;

	pip->childs = fork();
	if (pip->childs == 0)
	{
		pip->command = ft_command(pip, tmp->param[0], env, data);
		ft_close_fd(pip->infile, pip->outfile);
		ft_execve_one2(pip, tmp, data);
	}
	waitpid(pip->childs, &result, 0);
	if (WIFSIGNALED(result))
	{
		result = WTERMSIG(result) + 128;
		if (WTERMSIG(result) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(result) == SIGSEGV)
			write(STDERR_FILENO, "Segmentation fault (core dumped)\n", 33);
		return (result);
	}
	return (WEXITSTATUS(result));
}

void	ft_free_pip(t_pipex *pip)
{
	int	i;

	i = 0;
	free(pip->command);
	if (pip->path != NULL)
	{
		while (pip->path[i])
		{
			free(pip->path[i]);
			i++;
		}
		free(pip->path[i]);
		free(pip->path);
	}
}
