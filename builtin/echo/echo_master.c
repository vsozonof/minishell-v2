/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:48:29 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/26 14:57:09 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(char **param, t_data *data)
{
	int		i;
	int		flag;
	int		wr;

	i = 0;
	wr = ((flag = 0));
	while (param[++i])
	{
		if (ft_strnstr(param[i], "-n", 2) && !wr)
			flag = 1;
		else
		{
			wr = 1;
			if (param[i + 1])
				echo_printer(param[i]);
			else
				ft_putstr_fd(param[i], 1);
			if (errno == ENOSPC)
				set_status(data, 2, "no space left on device.", "echo");
		}
	}
	if (!flag)
		printf("\n");
	set_status(data, 0, NULL, NULL);
}

void	echo_printer(char *param)
{
	ft_putstr_fd(param, 1);
	write(1, " ", 1);
}
