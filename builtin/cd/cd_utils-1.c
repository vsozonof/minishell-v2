/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils-1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 05:27:00 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/27 21:47:59 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handling(int err, char *str, t_data *data)
{
	if (err == 2)
		printf("minishell: cd: %s: No such file or directory.\n", str);
	else if (err == 20)
		printf("minishell: cd: %s: is not a directory.\n", str);
	else if (err == 13)
		printf("minishell: cd: %s: Permission denied.\n", str);
	set_status(data, err, NULL, NULL);
}
