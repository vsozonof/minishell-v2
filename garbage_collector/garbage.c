/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jule-mer <jule-mer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 09:52:09 by firawar           #+#    #+#             */
/*   Updated: 2023/10/30 13:24:24 by jule-mer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bridge	*gc_create_bridge(t_list **collector)
{
	t_bridge	*new;
	t_list		*col;

	new = malloc(sizeof(t_easy));
	col = ft_lstnew(new);
	if (!new || !col)
	{
		ft_putstr_fd("Error in easy creation", 2);
		gc_dell(*collector);
		exit (1);
	}
	new->next = NULL;
	new->tokken = 0;
	ft_lstadd_back(collector, col);
	return (new);
}

t_easy	*gc_create_easy(t_list **collector)
{
	t_easy	*new;
	t_list	*col;

	new = malloc(sizeof(t_easy));
	col = ft_lstnew(new);
	if (!new || !col)
	{
		ft_putstr_fd("Error in easy creation", 2);
		gc_dell(*collector);
		exit (1);
	}
	new->next = NULL;
	ft_lstadd_back(collector, col);
	return (new);
}

t_use	*gc_create_use(t_list **collector)
{
	t_use	*new;
	t_list	*col;

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

char	**gc_alloc_char_r(t_list **collector, int size)
{
	char	**str;
	t_list	*new;

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

char	*gc_join_str(t_list **coll, const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		i2;

	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = gc_alloc_char(coll, i);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i2 = -1;
	while (s2[++i2])
		str[i + i2] = s2[i2];
	str[i + i2] = '\0';
	return (str);
}
