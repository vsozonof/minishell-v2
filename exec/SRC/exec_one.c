/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrub <rstrub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 07:37:59 by ertupop           #+#    #+#             */
/*   Updated: 2023/11/03 10:59:24 by rstrub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_exec_one(t_use *use, t_env **env, t_list *gc, t_pipex *pip)
{
	t_use	*tmp;
	t_sig	signal;
	t_exec	exec;

	tmp = NULL;
	ft_set_sa(&signal, ft_sig_handler_3);
	exec.tokken = ft_exec_one2(&use, &tmp, &pip);
	pip->s = dup(1);
	pip->i = dup(0);
	dup2(pip->infile, 0);
	dup2(pip->outfile, 1);
	if (exec.tokken == EXIT)
		ft_close_one(pip->s, pip->i);
	if (exec.tokken == NO)
		exec.result = ft_execve_one(env, pip, tmp, gc);
	else if (exec.tokken != NO)
		exec.result = ft_exec_bultins(tmp, env, gc, exec.tokken);
	dup2(pip->s, 1);
	dup2(pip->i, 0);
	close(pip->s);
	close(pip->i);
	(void) gc;
	ft_set_sa(&signal, ft_sig_handler);
	return (exec.result);
}

int	ft_exec_one2(t_use **use, t_use **tmp, t_pipex **pip)
{
	int		tokken;

	(*tmp) = (*use);
	(*pip)->outfile = 1;
	(*pip)->infile = 0;
	while ((*tmp))
	{
		if ((*tmp)->tokken == OUTFILE || (*tmp)->tokken == APPEND)
			(*pip)->outfile = (*tmp)->fd;
		if ((*tmp)->tokken == INFILE || (*tmp)->tokken == LIMITER)
			(*pip)->infile = (*tmp)->fd;
		(*tmp) = (*tmp)->next;
	}
	*tmp = *use;
	tokken = ft_check2((*tmp)->tab[0]);
	while (*tmp != NULL && (*tmp)->tokken != COMMAND)
		*tmp = (*tmp)->next;
	return (tokken);
}

int	ft_exec_bultins(t_use *use, t_env **env, t_list *gc, int tokken)
{
	if (tokken == CD)
		return (ft_cd(use->tab, *env, gc));
	else if (tokken == ECHO)
		return (ft_echo(use->tab));
	else if (tokken == ENV)
		return (ft_print_env(*env));
	else if (tokken == EXIT)
		return (ft_exit(use->tab, gc));
	else if (tokken == EXPORT)
		return (ft_export(use->tab, env, gc));
	else if (tokken == PWD)
		return (ft_pwd());
	else if (tokken == UNSET)
		return (ft_unset(gc, env, use->tab));
	return (NO);
}

int	ft_execve_one(t_env **env, t_pipex *pip, t_use *tmp, t_list *gc)
{
	int		result;
	t_sig	signal;

	pip->childs = fork();
	if (pip->childs == 0)
	{
		ft_set_sa_exec(&signal, SIG_DFL);
		pip->command = ft_command(pip, tmp->tab[0], gc, env);
		ft_close_fd(pip->infile, pip->outfile);
		ft_execve_one2(pip, tmp, gc, env);
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
