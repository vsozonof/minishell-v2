/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:20:12 by jule-mer          #+#    #+#             */
/*   Updated: 2024/06/10 07:55:58 by ertupop          ###   ########.fr       */
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
		ft_exec_all2(pip, &cmd->redirs);
		if (tmp == NULL)
			return (0);
		pip->childs = fork();
		if (pip->childs == 0)
			ft_exec_pipe(tmp, env, pip, data);
		ft_exec_all0(&cmd->redirs, &pip);
		ft_close_fd(pip->infile, pip->outfile);
		tmp = tmp->next;
	}
	close(pip->prev_pipes);
	return (ft_wait_lstchild(pip));
}

void	ft_exec_all0(t_redir **outfile, t_pipex **pip)
{
	if ((*pip)->prev_pipes != -1)
		close((*pip)->prev_pipes);
	(*pip)->prev_pipes = (*pip)->pipe[0];
	close((*pip)->pipe[1]);
	(*pip)->count_command ++;
	if ((*outfile) != NULL)
		(*outfile) = (*outfile)->next;
}
