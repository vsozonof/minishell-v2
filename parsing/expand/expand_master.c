/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:31:51 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/27 19:05:49 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_nodes(t_input *inp, t_data *data)
{
	t_input	*nav;

	nav = inp;
	while (nav)
	{
		data->input = nav->str;
		reg_expander(data, 0);
		if (!data->input)
			nav->str = ft_strdup("");
		else
		{
			if (is_there_quotes(data->input))
				data->input = quote_remover_v2(data->input);
			if (!data->input)
				nav->str = ft_strdup("");
			else
				nav->str = ft_strdup(data->input);
		}
		if (!nav->str)
			return (set_status(data, 12, "malloc error", "malloc"), 0);
		free(data->input);
		data->input = NULL;
		nav = nav->next;
	}
	return (1);
}
