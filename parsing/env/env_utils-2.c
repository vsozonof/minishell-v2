/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils-2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 22:20:24 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/28 01:07:51 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_side_env(t_prompt *ptr)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = ptr->env;
	ptr->nv = malloc(sizeof(char *) * (env_len(ptr->env) + 1));
	if (!ptr->nv)
		return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
	while (tmp)
	{
		ptr->nv[i] = ft_strdup(tmp->var);
		if (!ptr->nv[i])
			return (set_status(ptr->data, 12, "malloc error.", "malloc"), 0);
		i++;
		tmp = tmp->next;
	}
	ptr->nv[i] = NULL;
	return (1);
}

int	env_len(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	add_var_to_env(t_data *data, char *var)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	if (!tmp->next)
		return ;
	tmp->next->var = var;
	tmp->next->next = NULL;
	free_env_tab(data->pr->nv);
	create_side_env(data->pr);
}

void	del_var_from_env(t_data *data, char *var)
{
	t_env	*nav;
	t_env	*prev;
	int		len;

	nav = data->env;
	prev = data->env;
	len = ft_strlen(var);
	if (ft_strncmp(nav->var, var, len))
		nav = nav->next;
	while (nav)
	{
		if (!ft_strncmp(nav->var, var, len))
		{
			free(nav->var);
			prev->next = nav->next;
			free_env_tab(data->pr->nv);
			create_side_env(data->pr);
			return (free(nav));
		}
		else
		{
			prev = nav;
			nav = nav->next;
		}
	}
}
