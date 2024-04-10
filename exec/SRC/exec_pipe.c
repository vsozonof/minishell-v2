/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrub <rstrub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:31:37 by ertupop           #+#    #+#             */
/*   Updated: 2023/10/31 12:02:44 by rstrub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_exec_pipe(t_use *tmp, t_env **env, t_list *gc, t_pipex *pip)
{
	int		tokken;
	int		result;
	t_sig	signal;

	result = 0;
	ft_set_sa_exec(&signal, SIG_DFL);
	tokken = ft_check2(tmp->tab[0]);
	ft_exec_pipe2(pip);
	if (tokken == NO)
		ft_exec_pipe5(pip, env, tmp, gc);
	else
		result = ft_exec_pipe6(tmp, env, gc, tokken);
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
