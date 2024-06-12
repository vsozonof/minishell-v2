/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 07:03:36 by ertupop           #+#    #+#             */
/*   Updated: 2024/06/04 07:50:07 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**gc_alloc_tab_str(t_lst **collector, int size)
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

char	*gc_strdup(t_lst **collector, const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	str = gc_alloc_str(collector, i);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

char	*gc_alloc_str(t_lst **collector, int size)
{
	char	*str;
	t_lst	*new;

	str = malloc(sizeof(char ) * (size + 1));
	if (!str)
		return (NULL);
	new = ft_lstnew(str);
	ft_lstadd_back(collector, new);
	return (str);
}

char	**gc_tabdup(t_lst **collector, char **tab)
{
	int		size;
	char	**tabl;
	t_lst	*new;

	size = 0;
	while (tab[size])
		size++;
	tabl = gc_alloc_tab_str(collector, size);
	if (!tabl)
		return (NULL);
	new = ft_lstnew(tabl);
	ft_lstadd_back(collector, new);
	size = 0;
	while (tab[size])
	{
		tabl[size] = gc_strdup(collector, tab[size]);
		size++;
	}
	tabl[size] = NULL;
	return (tabl);
}
