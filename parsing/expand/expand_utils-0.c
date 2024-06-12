/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 02:16:29 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/26 09:25:53 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reg_expander(t_data *data, int i)
{
	if (!data->input)
		return ;
	while (data->input[i])
	{
		if (is_in_quotes(data->input, i) != 1 && (data->input[i] == '$'
				&& data->input[i + 1] && (!ft_is_whitespace(data->input[i + 1])
					&& expand_is_valid_char(data->input[i + 1]))))
		{
			reg_expand_splitter(data, i);
			reg_expand_joiner(data);
		}
		else if (!is_in_quotes(data->input, i)
			&& data->input[i] == '~'
			&& !data->input[i + 1])
			tilde_expander(data, i);
		else if ((!is_in_quotes(data->input, i)
				|| is_in_quotes(data->input, i) == 2)
			&& data->input[i] == '\\')
			backslash_expander(data, i);
		if (!data->input || ft_strlen(data->input) == 0
			|| i == (int)ft_strlen(data->input))
			break ;
		i++;
	}
}

void	reg_expand_joiner(t_data *data)
{
	if (!data->to_add)
	{
		free(data->input);
		data->input = strjoin_and_free(data->head, data->tail);
		if (ft_strlen(data->input) == 0)
		{
			free(data->input);
			data->input = NULL;
		}
	}
	else
	{
		data->new_head = strjoin_and_free(data->head, data->to_add);
		free(data->input);
		data->input = strjoin_and_free(data->new_head, data->tail);
	}
}

void	reg_expand_splitter(t_data *data, int i)
{
	if (data->input[i] == '$' && data->input[i + 1] == '$')
	{
		data->head = ft_substr(data->input, 0, (i));
		data->to_add = ft_strdup(data->pr->pid);
		data->tail = ft_substr(data->input, (i + 2), ft_strlen(data->input));
	}
	else if (data->input[i] == '$' && data->input[i + 1] == '0')
	{
		data->head = ft_substr(data->input, 0, (i));
		data->to_add = ft_strdup(data->pr->name);
		data->tail = ft_substr(data->input, (i + 2), ft_strlen(data->input));
	}
	else if (data->input[i] == '$' && data->input[i + 1] == '?')
	{
		data->head = ft_substr(data->input, 0, (i));
		data->to_add = ft_strdup(data->c_status);
		data->tail = ft_substr(data->input, (i + 2), ft_strlen(data->input));
	}
	else if (data->input[i] == '$' && expand_is_valid_char(data->input[i + 1]))
		search_and_split(data, i);
}

void	search_and_split(t_data *data, int i)
{
	int		c;
	char	*to_find;

	c = 0;
	if (data->input[i] == '$' && expand_is_valid_char(data->input[i + 1]))
		i++;
	c = i;
	while (data->input[c] && expand_is_valid_char(data->input[c])
		&& data->input[c] != '$')
		c++;
	to_find = ft_substr(data->input, i, (c - i));
	data->to_add = ft_get_env(data->env, to_find);
	if (to_find)
		free(to_find);
	data->head = ft_substr(data->input, 0, (i - 1));
	data->tail = ft_substr(data->input, c, ft_strlen(data->input));
}
