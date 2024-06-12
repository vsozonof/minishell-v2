/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:29:37 by vsozonof          #+#    #+#             */
/*   Updated: 2024/05/27 10:46:18 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	ret;

	ret = 0;
	if (!*s || fd == -1)
		return (0);
	i = -1;
	while (s[++i])
		ret = write(fd, &s[i], 1);
	return (ret);
}
