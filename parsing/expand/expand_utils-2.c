/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils-2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 02:54:33 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/26 09:43:18 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backslash_expander(t_data *data, int i)
{
	if (data->input[i] == '\\' && data->input[i + 1] == '\\')
	{
		data->head = ft_substr(data->input, 0, i);
		data->to_add = ft_strdup("\\");
		data->tail = ft_substr(data->input, (i + 2), ft_strlen(data->input));
		reg_expand_joiner(data);
	}
	else if (data->input[i] == '\\' && data->input[i + 1] != '\\')
	{
		data->head = ft_substr(data->input, 0, i);
		data->to_add = NULL;
		data->tail = ft_substr(data->input, (i + 1), ft_strlen(data->input));
		reg_expand_joiner(data);
	}
}

void	tilde_expander(t_data *data, int i)
{
	data->head = ft_substr(data->input, 0, i);
	data->to_add = ft_get_env(data->env, "HOME");
	data->tail = ft_substr(data->input, (i + 1), ft_strlen(data->input));
	reg_expand_joiner(data);
}

int	is_there_tilde(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '~')
			return (1);
	return (0);
}

char	*quote_remover_v2(char *str)
{
	char	**splitted;
	char	*tmp;
	int		i;

	i = 0;
	quote_flagger(str, -1, 0);
	splitted = ft_split(str, 27);
	if (!splitted[i])
		return (free(splitted), free(str), NULL);
	tmp = strjoin_and_free(splitted[i], splitted[i + 1]);
	i += 2;
	if (splitted[i - 1] == NULL)
	{
		free(str);
		free(splitted);
		return (tmp);
	}
	while (splitted[i])
	{
		tmp = strjoin_and_free(tmp, splitted[i]);
		i++;
	}
	free(str);
	free(splitted);
	return (tmp);
}

int	expand_is_valid_char(int c)
{
	if (ft_isalpha(c) || c == '?' || ft_isdigit(c) || c == '_' || c == '$')
		return (1);
	else
		return (0);
}
