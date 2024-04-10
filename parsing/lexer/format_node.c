/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:18:20 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/27 20:54:53 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	format_node(t_cmd *pr, t_input *inp, t_data *data)
{
	int	n;

	n = get_word_count(inp);
	pr->cmd = extract_command_name(inp);
	if (!pr->cmd)
		return (set_status(data, 12, "malloc error", "malloc"), 0);
	pr->param = malloc (sizeof(char *) * (n + 1));
	if (!pr->param)
		return (set_status(data, 12, "malloc error", "malloc"), 0);
	pr->param[n] = NULL;
	pr->env = data->pr->nv;
	if (!extract_params(inp, pr))
		return (set_status(data, 12, "malloc error", "malloc"), 0);
	n = get_redir_count(inp) + 1;
	if (!format_node_extra(pr, inp, data, n))
		return (0);
	return (1);
}

int	format_node_extra(t_cmd *pr, t_input *inp, t_data *data, int n)
{
	if (n > 1)
	{
		pr->redirs = malloc(sizeof(t_redir));
		if (!pr->redirs)
			return (set_status(data, 12, "maloc error", "malloc"), 0);
		if (!alloc_redir_list(pr, n))
			return (set_status(data, 12, "maloc error", "malloc"), 0);
		if (!extract_redirs(inp, pr))
			return (set_status(data, 12, "maloc error", "malloc"), 0);
	}
	else
		pr->redirs = NULL;
	pr->next = NULL;
	return (1);
}

int	extract_redirs(t_input *inp, t_cmd *pr)
{
	t_input	*nav;
	t_redir	*red;

	nav = inp;
	red = pr->redirs;
	while (nav)
	{
		if (nav->i == 1 && red)
		{
			red->type = set_redir_type(nav->str);
			nav = nav->next;
			if (nav)
			{
				red->file = ft_strdup(nav->str);
				if (!red->file)
					return (0);
				red = red->next;
			}
			else
				red->file = NULL;
		}
		else
			nav = nav->next;
	}
	return (1);
}

int	extract_params(t_input *inp, t_cmd *pr)
{
	t_input	*nav;
	int		i;

	nav = inp;
	i = 0;
	while (nav)
	{
		if (nav->i == 0 && ft_strlen(nav->str) != 0)
		{
			pr->param[i] = ft_strdup(nav->str);
			if (!pr->param[i])
				return (0);
			i++;
		}
		nav = nav->next;
	}
	return (1);
}

char	*extract_command_name(t_input *inp)
{
	t_input	*nav;

	nav = inp;
	while (nav)
	{
		if (nav->i == 0 && ft_strlen(nav->str) != 0)
			return (ft_strdup(nav->str));
		nav = nav->next;
	}
	return (ft_strdup(""));
}
