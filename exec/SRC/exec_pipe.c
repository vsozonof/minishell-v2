/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:31:37 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/12 16:51:49 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_pipe(t_cmd *tmp, t_env **env, t_pipex *pip, t_data **data)
{
	int		tokken;
	int		result;

	result = 0;
	if (tmp->param[0] == NULL)
		return (0);
	tokken = ft_check2(tmp->param[0]);
	ft_exec_pipe2(pip);
	if (tokken == NO)
		ft_exec_pipe5(pip, env, tmp, data);
	else
		result = ft_exec_bultins(tmp, env, tokken, data);
	ft_close_fd(pip->infile, pip->outfile);
	exit (result);
}

void	ft_exec_pipe2(t_pipex *pip)
{
	if (pip->infile != 0)
	{
		dup2(pip->infile, 0);
		close(pip->infile);
	}
	else
	{
		if (pip->prev_pipes != -1)
		{
			dup2(pip->prev_pipes, 0);
			close(pip->prev_pipes);
		}
		close(pip->pipe[0]);
	}
	if (pip->outfile != 1)
	{
		dup2(pip->outfile, 1);
		close(pip->outfile);
	}
	else if (pip->count_command != pip->nbr_command - 1)
	{
		dup2 (pip->pipe[1], 1);
		close(pip->pipe[1]);
	}
}
