/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:37:41 by vsozonof          #+#    #+#             */
/*   Updated: 2024/04/10 19:09:57 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_finder(t_cmd *node, t_data *data)
{
	t_redir	*nav1;
	t_cmd	*nav2;

	nav2 = node;
	while (nav2)
	{
		nav1 = nav2->redirs;
		while (nav1)
		{
			if (nav1->type == 3)
			{
				if (!do_heredoc(nav1->file, nav1, data))
					return (0);
				nav1 = nav1->next;
			}
			else
				nav1 = nav1->next;
		}
		nav2 = nav2->next;
	}
	return (1);
}

int	do_heredoc(char *delimiter, t_redir *redir_node, t_data *data)
{
	static int		n;
	char			*tmp_fname;
	int				fd;

	n = 0;
	tmp_fname = get_tmp_filename(data);
	fd = open(tmp_fname, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (set_status(data, 2, "error detected", "open"), 0);
	data->here_doc_fd[n] = fd;
	n++;
	g_status = 2;
	if (!(do_heredoc_extra(delimiter, fd)))
	{
		free(tmp_fname);
		return (0);
	}
	free(delimiter);
	redir_node->file = tmp_fname;
	redir_node->fd = fd;
	return (1);
}

int	do_heredoc_extra(char *delimiter, int fd)
{
	int		dup_save;
	char	*heredoc_input;

	dup_save = dup(0);
	while (42)
	{
		heredoc_input = readline("> ");
		if (g_status == 1)
			return (dup2(dup_save, 0), close(dup_save), 0);
		if (!heredoc_input)
			break ;
		if (!ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter)))
		{
			free(heredoc_input);
			break ;
		}
		ft_putstr_fd(heredoc_input, fd);
		write(fd, "\n", 1);
		free(heredoc_input);
	}
	close(dup_save);
	return (1);
}

char	*get_tmp_filename(t_data *data)
{
	char		*str;
	int			i;
	int			fd;

	fd = open("/dev/random", O_RDONLY);
	if (!fd)
		return (set_status(data, 2, "error detected", "open"), NULL);
	str = malloc(sizeof(char) * 21);
	if (!str)
		return (set_status(data, 12, "malloc error", "malloc"), NULL);
	read(fd, str, 16);
	i = 1;
	str[0] = '.';
	while (i <= 15)
	{
		str[i] = (str[i] % 25) + 'a';
		i++;
	}
	str[16] = '.';
	str[17] = 't';
	str[18] = 'x';
	str[19] = 't';
	str[20] = '\0';
	close(fd);
	return (str);
}
