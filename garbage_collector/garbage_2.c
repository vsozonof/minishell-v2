/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:01:19 by jule-mer          #+#    #+#             */
/*   Updated: 2024/05/27 13:10:27 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_use	*gc_alloc_use(t_lst **collector)
{
	t_use	*new;
	t_lst	*col;

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

t_env	*gc_alloc_env(t_lst **collector)
{
	t_env	*new;
	t_lst	*col;

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
