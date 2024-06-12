/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 04:46:20 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/26 14:40:04 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_status(t_data *data, int status, char *str, char *cmd)
{
	if (cmd || str)
		ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putchar_fd(':', 2);
	}
	if (str)
	{
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
	if (data->c_status)
		free(data->c_status);
	data->i_status = status;
	data->c_status = ft_itoa(status);
}
