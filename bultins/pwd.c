/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:28:57 by ertupop           #+#    #+#             */
/*   Updated: 2024/05/27 10:47:31 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(str, 0);
	if (str == NULL)
		return (1);
	ft_putstr_fd(str, 1);
	write(1, "\n", 1);
	free(str);
	return (0);
}
