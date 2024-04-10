/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:01:19 by jule-mer          #+#    #+#             */
/*   Updated: 2023/09/06 23:20:59 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*gc_strdup(t_list **collector, const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	str = gc_alloc_char(collector, i);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

t_use	*gc_alloc_use(t_list **collector)
{
	t_use	*new;
	t_list	*col;

	new = malloc(sizeof(t_use));
	col = ft_lstnew(new);
	if (!new || !col)
	{
		ft_putstr_fd("Error in easy creation", 2);
		gc_dell(*collector);
		exit (1);
	}
	new->next = NULL;
	new->tab = NULL;
	new->tokken = 0;
	ft_lstadd_back(collector, col);
	return (new);
}

t_env	*gc_alloc_env(t_list **collector)
{
	t_env	*new;
	t_list	*col;

	new = malloc(sizeof(t_env));
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
