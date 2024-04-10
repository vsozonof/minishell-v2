/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 04:46:20 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/12 09:46:26 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_status(t_data *data, int status, char *str, char *cmd)
{
	if (cmd || str)
		printf("minishell: ");
	if (cmd)
		printf("%s:", cmd);
	if (str)
		printf(" %s\n", str);
	if (data->c_status)
		free(data->c_status);
	data->i_status = status;
	data->c_status = ft_itoa(status);
}
