/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:14:40 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/07 09:37:42 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_nbr_cmd(t_cmd *cmd)
{
	int		command;
	t_cmd	*tmp;

	tmp = cmd;
	command = 0;
	while (tmp)
	{
		command++;
		tmp = tmp->next;
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
