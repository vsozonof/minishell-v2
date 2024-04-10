/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:15:28 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/27 18:28:07 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multi_node_handler(t_data *data, int i)
{
	char	***tab;

	data->inp->cmds = pipes_splitter(data->input, '|', data);
	tab = malloc(sizeof(char **) * (data->n_cmds + 1));
	if (!tab || !data->inp->cmds)
		return (set_status(data, 12, "malloc error", "malloc"), 0);
	while (data->inp->cmds[i])
	{
		free(data->input);
		data->input = data->inp->cmds[i];
		tab[i] = input_to_lst(data);
		i++;
	}
	free(data->inp->cmds);
	data->inp->cmds = ((tab[i] = NULL));
	data->multi_inp = alloc_struct(data->multi_inp, (data->n_cmds + 1));
	if (!data->multi_inp)
		return (set_status(data, 12, "malloc error", "malloc"), 0);
	multi_input_to_lst(data->multi_inp, tab, 0, 0);
	i = -1;
	while (data->multi_inp[++i])
		identify_nodes(data->multi_inp[i]);
	multi_node_formatting(data->multi_inp, data);
	return (1);
}

int	multi_input_to_lst(t_input **ptr, char ***tab, int i, int n)
{
	t_input	*nav;

	while (ptr[i])
	{
		nav = ptr[i];
		while (tab[i][n])
		{
			nav->str = ft_strdup(tab[i][n]);
			if (tab[i][n + 1])
			{
				nav->next = malloc(sizeof(t_input));
				if (!nav->next)
					return (0);
				nav = nav->next;
			}
			else
				nav->next = NULL;
			n++;
		}
		n = 0;
		i++;
	}
	free_tri_table(tab);
	return (1);
}

void	multi_node_formatting(t_input **inp, t_data *data)
{
	t_cmd	*ptr;
	t_cmd	*nav;
	int		i;

	i = -1;
	while (inp[++i])
		expand_nodes(inp[i], data);
	i = 0;
	ptr = malloc(sizeof(t_cmd));
	if (!ptr)
		return ;
	data->exec = ptr;
	alloc_multi_nodes(inp, ptr);
	nav = ptr;
	while (inp[i])
	{
		multi_format_node(nav, inp[i], data);
		nav = nav->next;
		i++;
	}
	nav = NULL;
	free(data->inp);
	data->inp = NULL;
}

void	multi_format_node(t_cmd *pr, t_input *inp, t_data *data)
{
	int	n;

	n = get_word_count(inp);
	pr->cmd = extract_command_name(inp);
	pr->param = malloc(sizeof(char *) * (n + 1));
	pr->param[n] = NULL;
	pr->env = data->pr->nv;
	extract_params(inp, pr);
	n = get_redir_count(inp) + 1;
	if (n > 1)
	{
		pr->redirs = malloc(sizeof(t_redir));
		if (!pr->redirs)
			return ;
		alloc_redir_list(pr, n);
		extract_redirs(inp, pr);
	}
	else
		pr->redirs = NULL;
}
