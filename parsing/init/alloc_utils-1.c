/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils-1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:11:25 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/27 23:28:15 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_redir_list(t_cmd *pr, int n)
{
	int		i;
	t_redir	*p;

	p = pr->redirs;
	i = 1;
	while (i < n - 1)
	{
		p->next = malloc(sizeof(t_redir));
		if (!p->next)
			return (0);
		p = p->next;
		i++;
	}
	p -> next = NULL;
	return (1);
}

t_input	**alloc_struct(t_input **ptr, int n)
{
	int	i;

	i = 0;
	ptr = malloc(sizeof(t_input *) * n);
	while (i < (n - 1))
	{
		ptr[i] = malloc(sizeof(t_input));
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

t_cmd	*alloc_node(t_cmd *pr)
{
	pr = malloc(sizeof(t_cmd));
	if (!pr)
		return (NULL);
	pr->cmd = NULL;
	pr->param = NULL;
	pr->next = NULL;
	pr->redirs = NULL;
	return (pr);
}

int	alloc_multi_nodes(t_input **inp, t_cmd *pr)
{
	int		i;
	t_cmd	*nav;

	nav = pr;
	i = 1;
	while (inp[i])
	{
		nav -> next = malloc(sizeof(t_cmd));
		if (!nav -> next)
			return (0);
		nav->cmd = NULL;
		nav->param = NULL;
		i++;
		nav = nav -> next;
	}
	nav->next = NULL;
	return (1);
}

t_input	*alloc_input_struct(void)
{
	t_input	*inp;

	inp = malloc(sizeof(t_input));
	if (!inp)
		return (NULL);
	inp->cmds = NULL;
	inp->next = NULL;
	inp->str = NULL;
	return (inp);
}
