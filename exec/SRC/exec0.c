/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:20:12 by jule-mer          #+#    #+#             */
/*   Updated: 2024/07/01 15:08:11 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_all(t_cmd *cmd, t_env **env, t_pipex *pip, t_data **data)
{
	t_cmd	*tmp;

	tmp = cmd;
	pip->count_command = 0;
	pip->prev_pipes = -1;
	while (pip->count_command < pip->nbr_command)
	{
		if (tmp == NULL)
			return (0);
		ft_exec_all_open_file(pip, tmp->redirs);
		pip->childs = fork();
		if (pip->childs == 0)
			ft_exec_pipe(tmp, env, pip, data);
		ft_exec_all0(&pip);
		ft_close_fd(pip->infile, pip->outfile);
		tmp = tmp->next;
	}
	close(pip->prev_pipes);
	return (ft_wait_lstchild(pip));
}

void	ft_exec_all0(t_pipex **pip)
{
	if ((*pip)->prev_pipes != -1)
		close((*pip)->prev_pipes);
	(*pip)->prev_pipes = (*pip)->pipe[0];
	close((*pip)->pipe[1]);
	(*pip)->count_command ++;
}

void	ft_open_outfile(t_pipex *pip, t_redir *redir)
{
	if (redir->type == OUTFILE)
	{
		if (pip->outfile != 1)
			close(pip->outfile);
		pip->outfile = open(redir->file, O_TRUNC
				| O_CREAT | O_RDWR, 00644);
	}
	else if (redir->type == APPEND)
	{
		if (pip->outfile != 1)
			close(pip->outfile);
		pip->outfile = open(redir->file, O_APPEND | O_CREAT
				| O_RDWR, 00644);
	}
}

void	ft_open_infile(t_pipex *pip, t_redir *redir)
{
	if (redir->type == INFILE)
	{
		if (pip->infile != 0)
			close(pip->infile);
		pip->infile = open(redir->file, O_RDONLY, 00644);
	}
	else if (redir->type == LIMITER)
	{
		if (pip->infile != 0)
			close(pip->infile);
		pip->infile = open(redir->file, O_RDONLY, 00644);
		unlink(redir->file);
	}
}
