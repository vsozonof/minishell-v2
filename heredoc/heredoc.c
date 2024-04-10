/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 08:13:24 by ertupop           #+#    #+#             */
/*   Updated: 2023/11/01 11:13:43 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_acces_heredoc(t_use *use, t_list **gc)
{
	int		fd;
	char	*str;
	char	*number;
	char	*heredoc;
	int		i;

	fd = -1;
	i = 0;
	str = ft_strdup(".tmp_heredoc");
	number = NULL;
	heredoc = NULL;
	if (str == NULL)
		return (-1);
	while (fd == -1 && ++i < 101)
		fd = ft_heredoc_while(i, str, number, heredoc);
	number = ft_itoa(i);
	use->file_name = gc_join_str(gc, str, number);
	free(number);
	number = NULL;
	free(str);
	str = NULL;
	ft_acces_free(str, number, heredoc);
	return (fd);
}

int	ft_heredoc_while(int i, char *str, char *number, char *heredoc)
{
	int	fd;

	number = ft_itoa(i);
	if (number == NULL)
		return (-1);
	heredoc = ft_strjoin(str, number);
	free(number);
	number = NULL;
	if (heredoc == NULL)
		return (-1);
	if (access(heredoc, 0) == 0)
	{
		free(heredoc);
		return (-1);
	}
	fd = open(heredoc, O_CREAT | O_RDWR | O_TRUNC, 00644);
	free(heredoc);
	heredoc = NULL;
	return (fd);
}

void	ft_acces_free(char *str, char *number, char *heredoc)
{
	if (number != NULL)
		free(number);
	if (heredoc != NULL)
		free(heredoc);
	if (str != NULL)
		free(str);
}

void	ft_heredoc(int fd, const char *end, t_env *env)
{
	char	*str;
	t_easy	*work;
	t_list	*gc;
	int		i;

	gc = NULL;
	gc_alloc_char(&gc, 1);
	ft_exit_sig_heredoc(2, NULL, gc, 0);
	while (1)
	{
		i = 0;
		work = NULL;
		str = readline(">");
		if (str == NULL || ft_strstr(str, end) == 0)
		{
			ft_heredoc2(end, str, gc, fd);
			return ;
		}
		while (str[i])
			ft_start_easy_here(&work, &gc, &i, str);
		free(str);
		str = NULL;
		ft_work(work, gc, fd, env);
	}
}

void	ft_start_easy_here(t_easy **easy, t_list **collector, int *i, char *str)
{
	t_easy	*new;

	new = gc_create_easy(collector);
	ft_init_easy(new);
	new->c = str[(*i)++];
	if (new->c == ' ')
		new->space = 1;
	ft_check_quote(&new);
	ft_lstadd_back_easy(easy, new);
}
