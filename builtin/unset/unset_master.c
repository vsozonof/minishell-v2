/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_master.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:54:08 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/23 14:03:57 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(t_data *data)
{
	int		i;

	i = 1;
	while (data->exec->param[i])
	{
		do_unset(data->exec->param[i], data);
		i++;
	}
}

void	do_unset(char *args, t_data *data)
{
	if (!ft_get_env_node(data->env, args))
		return ;
	else
		del_var_from_env(data, args);
}
