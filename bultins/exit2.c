/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrub <rstrub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 07:28:10 by rstrub            #+#    #+#             */
/*   Updated: 2023/10/30 07:31:24 by rstrub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit5(char **tab)
{
	ft_putstr_fd("exit\nminishell: exit : ", 1);
	ft_putstr_fd(tab[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
}
