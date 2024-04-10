/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:54:00 by jule-mer          #+#    #+#             */
/*   Updated: 2023/11/01 16:05:06 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_execve_one2(t_pipex *pip, t_use *tmp, t_list *gc, t_env **env)
{
	if (pip->command != NULL)
		pip->env = ft_make_env_tab(*env);
	if (pip->command == NULL)
	{
		ft_fprintf(2, "minishell : ");
		ft_fprintf(2, "%s: command not found\n", tmp->tab[0]);
		g_exit = 127;
		close(pip->infile);
		close(pip->outfile);
		close(pip->s);
		close(pip->i);
		gc_dell(gc);
		exit(127);
	}
	else if (execve(pip->command, tmp->tab, pip->env) == -1)
	{
		ft_free_envp(pip->env);
		ft_free_pip(pip);
		ft_exit(NULL, gc);
	}
}
