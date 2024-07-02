/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:14:42 by vsozonof          #+#    #+#             */
/*   Updated: 2024/07/02 11:55:50 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_node_handler(t_data *data)
{
	char	**tab;
	t_cmd	*ptr;

	ptr = NULL;
	ptr = alloc_node(ptr);
	if (!ptr)
		return (set_status(data, 12, "malloc error", "malloc"), 0);
	data->exec = ptr;
	tab = input_to_lst(data);
	// annoying_quotes_handler(tab);
	if (!tab)
		return (ft_split_free(tab),
			set_status(data, 12, "malloc error", "malloc"), 0);
	if (!put_input_to_lst(data->inp, tab, data))
		return (0);
	identify_nodes(data->inp);
	if (!expand_nodes(data->inp, data))
		return (0);
	if (!format_node(ptr, data->inp, data))
		return (0);
	return (1);
}

int	put_input_to_lst(t_input *ptr, char **tab, t_data *data)
{
	int		i;
	t_input	*nav;

	i = 0;
	nav = ptr;
	while (tab[i])
	{
		nav->str = ft_strdup(tab[i]);
		if (!nav->str)
			return (set_status(data, 12, "malloc error", "malloc"), 0);
		if (tab[i + 1])
		{
			nav->next = malloc(sizeof(t_input));
			if (!nav->next)
				return (set_status(data, 12, "malloc error", "malloc"), 0);
			nav = nav->next;
		}
		else
			nav->next = NULL;
		i++;
	}
	ft_split_free(tab);
	return (1);
}
