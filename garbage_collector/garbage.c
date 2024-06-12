/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 09:52:09 by firawar           #+#    #+#             */
/*   Updated: 2024/05/27 12:53:06 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_use	*gc_create_use(t_lst **collector)
{
	t_use	*new;
	t_lst	*col;

	new = malloc(sizeof(t_use));
	col = ft_lstnew(new);
	if (!new || !col)
	{
		ft_putstr_fd("Error in usable creation", 2);
		gc_dell(*collector);
		exit (1);
	}
	new->next = NULL;
	ft_lstadd_back(collector, col);
	return (new);
}

char	**gc_alloc_char_r(t_lst **collector, int size)
{
	char	**str;
	t_lst	*new;

	str = malloc(sizeof(char *) * (size + 1));
	if (!str)
	{
		gc_dell(*collector);
		exit(1);
	}
	str[size] = NULL;
	new = ft_lstnew(str);
	ft_lstadd_back(collector, new);
	return (str);
}

char	*gc_join_str(t_lst **coll, const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		i2;

	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = gc_alloc_str(coll, i);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i2 = -1;
	while (s2[++i2])
		str[i + i2] = s2[i2];
	str[i + i2] = '\0';
	return (str);
}
