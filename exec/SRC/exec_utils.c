/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostrub <rostrub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:11:25 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/14 06:41:33 by rostrub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_openfd(t_cmd **cmd, t_redir **tmp, t_pipex **pip)
{
	int		tokken;

	(*pip)->outfile = 1;
	(*pip)->infile = 0;
	while (*tmp)
	{
		if ((*tmp)->type == OUTFILE)
			(*pip)->outfile = open((*tmp)->file, O_TRUNC
					| O_CREAT | O_RDWR, 00644);
		else if ((*tmp)->type == APPEND)
			(*pip)->outfile = open((*tmp)->file, O_APPEND | O_CREAT
					| O_RDWR, 00644);
		else if ((*tmp)->type == INFILE)
			(*pip)->infile = open((*tmp)->file, O_RDONLY, 00644);
		*tmp = (*tmp)->next;
	}
	tokken = ft_check2((*cmd)->param[0]);
	return (tokken);
}

int	ft_exec_bultins(t_cmd *cmd, t_env **env, int tokken, t_data **data)
{
	if (tokken == CD)
		return (ft_cd(cmd->param, *env));
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
