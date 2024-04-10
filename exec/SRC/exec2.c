/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:14:40 by ertupop           #+#    #+#             */
/*   Updated: 2023/09/27 09:10:50 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_create_pipe(int count, int *pipes)
{
	if (count % 2 == 0)
	{
		pipe(pipes);
	}
	else
	{
		pipe(pipes + 2);
	}
	return (0);
}

int	ft_init_fd(t_pipex *pip, t_use *use)
{
	t_use	*tmp;
	int		command;

	command = 0;
	tmp = use;
	(void) pip;
	while (tmp)
	{
		if (tmp->tokken == PIPE)
			command++;
		tmp = tmp->next;
	}
	if (command > 0)
		command++;
	tmp = use;
	if (command == 0)
	{
		while (tmp)
		{
			if (tmp->tokken == COMMAND)
			command++;
			tmp = tmp->next;
		}
	}
	return (command);
}

void	ft_close_fd(int in, int out)
{
	if (in != 0)
		close (in);
	if (out != 1)
		close (out);
}

int	ft_check2(char *s)
{
	if (ft_strcmp(s, "cd") == 0)
		return (CD);
	if (ft_strcmp("echo", s) == 0)
		return (ECHO);
	if (ft_strcmp("env", s) == 0)
		return (ENV);
	if (ft_strcmp("exit", s) == 0)
		return (EXIT);
	if (ft_strcmp("export", s) == 0)
		return (EXPORT);
	if (ft_strcmp("pwd", s) == 0)
		return (PWD);
	if (ft_strcmp("unset", s) == 0)
		return (UNSET);
	return (NO);
}

void	ft_lunch_heredoc(t_use *here, t_env *env, t_list *gc)
{
	pid_t	child;
	t_sig	signal;

	child = fork();
	ft_set_sa(&signal, ft_sig_handler_2);
	if (child == 0)
	{
		ft_exit_sig_heredoc(1, here->eof, gc, here->fd);
		ft_set_sa(&signal, ft_sig_handler_heredoc);
		gc_dell_one(gc, &here->file_name);
		ft_heredoc(here->fd, here->eof, env);
		close(here->fd);
		here = here->next;
		ft_clear_here(here, gc);
		gc_dell(gc);
		exit(0);
	}
	close(here->fd);
	waitpid(child, NULL, 0);
	ft_set_sa(&signal, ft_sig_handler);
}
