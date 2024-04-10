/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:05:39 by jule-mer          #+#    #+#             */
/*   Updated: 2023/09/27 09:22:15 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc2(const char *end, char *str, t_list *gc, int fd)
{
	if (str == NULL)
	{
		ft_fprintf(2, "minishell: warning heredoc \
		delimited by end of file (wanted `%s')\n", end);
	}
	free(str);
	if (gc)
		gc_dell(gc);
	close (fd);
	return ;
}

void	ft_heredoc3(t_easy *work, t_list *gc, int fd)
{
	t_easy	*dell;

	while (work)
	{
		ft_putchar_fd(work->c, fd);
		work = work->next;
	}
	ft_putchar_fd('\n', fd);
	while (work)
	{
		dell = work;
		work = work->next;
		gc_dell_one(gc, &dell);
	}
}

void	ft_work(t_easy *work, t_list *gc, int fd, t_env *env)
{
	ft_good_quote(&work);
	ft_expand(&work, &gc, &env);
	ft_skip_space(&work, &gc);
	ft_heredoc3(work, gc, fd);
}
