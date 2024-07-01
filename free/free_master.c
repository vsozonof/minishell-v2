/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:29:11 by vsozonof          #+#    #+#             */
/*   Updated: 2024/07/01 09:50:11 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_master(t_data *data)
{
	int	i;

	i = -1;
	if (data->input)
		free(data->input);
	if (data->inp)
		free_input_lst(data->inp);
	if (data->multi_inp)
	{
		while (data->multi_inp[++i])
			free_input_lst(data->multi_inp[i]);
		free(data->multi_inp);
	}
	free_cmd_nodes(data->exec);
	if (data->here_doc_fd)
		free(data->here_doc_fd);
}

void	free_cmd_nodes(t_cmd *nodes)
{
	t_redir	*tmp1;
	t_redir	*nav;
	t_cmd	*tmp2;

	while (nodes)
	{
		free (nodes->cmd);
		ft_split_free(nodes->param);
		nav = nodes->redirs;
		while (nav)
		{
			free(nav->file);
			tmp1 = nav;
			nav = nav->next;
			free(tmp1);
		}
		tmp2 = nodes;
		nodes = nodes->next;
		free(tmp2);
	}
}

void	free_tri_table(char ***tab)
{
	int	i;
	int	n;

	i = ((n = 0));
	while (tab[i])
	{
		while (tab[i][n])
		{
			free(tab[i][n]);
			n++;
		}
		free(tab[i]);
		i++;
		n = 0;
	}
	free(tab);
}

void	free_input_lst(t_input *lst)
{
	t_input	*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		if (lst->str)
			free(lst->str);
		free(lst);
		lst = tmp;
	}
	lst = NULL;
}

void	free_end_of_program(t_prompt *p)
{
	clear_history();
	if (p->user)
		free(p->user);
	if (p->w_d)
		free(p->w_d);
	if (p->post)
		free(p->post);
	if (p->env)
		free_env(p->env);
	if (p->nv)
		free_env_tab(p->nv);
	if (p->name)
		free(p->name);
	if (p->pid)
		free(p->pid);
	if (p->data->c_status)
		free(p->data->c_status);
}
