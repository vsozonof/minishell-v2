/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostrub <rostrub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:54:00 by jule-mer          #+#    #+#             */
/*   Updated: 2024/06/14 11:35:10 by rostrub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execve_one2(t_pipex *pip, t_cmd *tmp, t_data **data)
{
	if (pip->command == NULL)
	{
		ft_fprintf(2, "minishell : ");
		ft_fprintf(2, "%s: command not found\n", tmp->param[0]);
		close(pip->infile);
		close(pip->outfile);
		close(pip->out);
		close(pip->in);
		free_master(*data);
		free_end_of_program((*data)->pr);
		exit(127);
	}
	else if (execve(pip->command, tmp->param, tmp->env) == -1)
	{
		ft_free_pip(pip);
		execute_exit(NULL, *data);
	}
}
