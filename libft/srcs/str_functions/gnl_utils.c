/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:02:00 by vsozonof          #+#    #+#             */
/*   Updated: 2023/03/09 21:41:54 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash[FOPEN_MAX];

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stash[fd] = read_and_fill_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	stash[fd] = extract_from_stash(stash[fd]);
	return (line);
}

char	*read_and_fill_stash(int fd, char *stash)
{
	char		*tmp;
	int			counter;

	counter = 1;
	while (ft_find_newline(stash) == -1 && counter != 0)
	{
		tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
		counter = read(fd, tmp, BUFFER_SIZE);
		if (counter == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[counter] = '\0';
		stash = free_and_join_stash(stash, tmp);
		free(tmp);
	}
	return (stash);
}

char	*free_and_join_stash(char *stash, char *tmp)
{
	char	*new_stash;

	new_stash = ft_strjoin_gnl(stash, tmp);
	free (stash);
	return (new_stash);
}

char	*extract_from_stash(char *stash)
{
	char	*new_stash;
	int		len;

	len = (ft_strlen_gnl(stash) - ft_find_newline(stash));
	if (!stash || ft_find_newline(stash) == -1)
	{
		free(stash);
		return (NULL);
	}
	else
		new_stash = ft_substr_gnl(stash, (ft_find_newline(stash) + 1), len);
	free(stash);
	return (new_stash);
}

char	*get_line(char *stash)
{
	char	*new_line;

	if (!stash)
		return (NULL);
	if (ft_find_newline(stash) >= 0)
		new_line = ft_substr_gnl(stash, 0, (ft_find_newline(stash) + 1));
	else
		new_line = ft_substr_gnl(stash, 0, ft_strlen_gnl(stash));
	return (new_line);
}
