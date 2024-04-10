/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:45:30 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/21 13:21:57 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(t_data *data)
{
	t_env	*nav;

	nav = data->env;
	while (nav)
	{
		printf("%s\n", nav->var);
		nav = nav->next;
	}
}
