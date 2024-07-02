/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:11:43 by ertupop           #+#    #+#             */
/*   Updated: 2024/07/02 11:17:28 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec(t_cmd **cmd, t_env **env, t_data **data)
{
	t_pipex	pipex;

	pipex.outfile = 1;
	(void) env;
	pipex.nbr_command = ft_nbr_cmd(*cmd);
	if (pipex.nbr_command == 0)
		return (ft_open_close(*cmd), (*data)->i_status);
	if (pipex.nbr_command == 1)
		(*data)->i_status = ft_exec_one(*cmd, env, &pipex, data);
	else
		(*data)->i_status = ft_exec_all(*cmd, env, &pipex, data);
	ft_close_fd(pipex.infile, pipex.outfile);
	free((*data)->c_status);
	(*data)->c_status = ft_itoa((*data)->i_status);
	return ((*data)->i_status);
}

void	ft_exec_all_open_file(t_pipex *pip, t_redir *redir)
{
	if (pipe(pip->pipe))
		return ;
	pip->outfile = 1;
	pip->infile = 0;
	while (redir)
	{
		if (redir->type == OUTFILE || redir->type == APPEND)
			ft_open_outfile(pip, redir);
		else if (redir->type == INFILE || redir->type == LIMITER)
			ft_open_infile(pip, redir);
		redir = redir->next;
	}
}

int	ft_wait_lstchild(t_pipex *pip)
{
	int		lastchilds;
	int		tmprtr;
	int		pidw;

	tmprtr = 0;
	pidw = waitpid(-1, &tmprtr, 0);
	while (pip->count_command != 0)
	{
		if (pidw == pip->childs)
			lastchilds = tmprtr;
		pidw = waitpid(-1, &tmprtr, 0);
		pip->count_command--;
	}
	if (WIFSIGNALED(lastchilds))
	{
		lastchilds = WTERMSIG(lastchilds) + 128;
		if (WTERMSIG(lastchilds) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(lastchilds) == SIGSEGV)
			write(STDERR_FILENO, "Segmentation fault (core dumped)\n", 33);
		return (lastchilds);
	}
	return (WEXITSTATUS(lastchilds));
}

int	ft_close_pipe(int count, int *pipe, int nbr_command, t_pipex *pip)
{
	if (pip->outfile != 0)
		close(pip->outfile);
	if (pip->infile != 1)
		close(pip->infile);
	if (count == 0)
		close(pipe[1]);
	else if (count == nbr_command -1)
	{
		if (count % 2 == 0)
			close(pipe[2]);
		else
			close(pipe[0]);
	}
	else if (count % 2 == 0)
	{
		close(pipe[1]);
		close(pipe[2]);
	}
	else
	{
		close(pipe[0]);
		close(pipe[3]);
	}
	return (0);
}
