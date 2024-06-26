/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:11:25 by ertupop           #+#    #+#             */
/*   Updated: 2024/07/01 15:14:12 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_openfd(t_cmd **cmd, t_redir *tmp, t_pipex **pip)
{
	int		tokken;

	(*pip)->outfile = 1;
	(*pip)->infile = 0;
	while (tmp)
	{
		if (tmp->type == OUTFILE || tmp->type == APPEND)
			ft_open_outfile(*pip, tmp);
		else if (tmp->type == INFILE || tmp->type == LIMITER)
			ft_open_infile(*pip, tmp);
		tmp = tmp->next;
	}
	tokken = ft_check2((*cmd)->param[0]);
	return (tokken);
}

int	ft_exec_bultins(t_cmd *cmd, t_env **env, int tokken, t_data **data)
{
	if (tokken == CD)
		return (ft_cd(cmd->param, *env, data));
	else if (tokken == ECHO)
		return (ft_echo(cmd->param));
	else if (tokken == ENV)
		return (ft_print_env(*env));
	else if (tokken == EXIT)
	{
		execute_exit(cmd->param, *data);
		return ((*data)->i_status);
	}
	else if (tokken == EXPORT)
		return (ft_export(cmd->param, env));
	else if (tokken == PWD)
		return (ft_pwd());
	else if (tokken == UNSET)
		return (ft_unset(env, cmd->param));
	return (NO);
}

void	ft_open_close(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == LIMITER)
			{
				fd = open(redir->file, O_RDONLY, 00644);
				unlink(redir->file);
				if (fd != -1)
					close(fd);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
