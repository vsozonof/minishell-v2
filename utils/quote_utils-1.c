/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils-1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 03:12:41 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/22 10:39:32 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unquote_command(t_data *data)
{
	char	*to_extract;
	char	*rest;
	int		i;

	i = 0;
	while (data->input[i])
	{
		if ((!is_in_quotes(data->input, i) && ft_is_whitespace(data->input[i])))
			break ;
		i++;
	}
	to_extract = ft_substr(data->input, 0, i);
	rest = ft_substr(data->input, (i), (ft_strlen(data->input)));
	free(data->input);
	data->input = to_extract;
	reg_expander(data, 0);
	to_extract = data->input;
	data->input = rest;
	reg_expander(data, 0);
	rest = data->input;
	if (to_extract && is_there_quotes(to_extract))
		to_extract = quote_remover_v2(to_extract);
	data->input = strjoin_and_free(to_extract, rest);
}
