/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:59:39 by ertupop           #+#    #+#             */
/*   Updated: 2023/03/16 09:08:31 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft.h"

int		ft_fprintf(int std, const char *string, ...);
int		ft_putchar_fd_print(int std, int c);
int		ft_putstr_fd_print(int std, char *s);
int		ft_putnbr_fd_print(int std, int c);
int		ft_puthexa_fd_print(unsigned int nbr, char *base);
int		ft_putunsign_fd_print(int std, unsigned int nbr);
int		ft_putvoid_fd_print(int std, unsigned long long n);
void	ft_put_fd(int std, char c);
#endif
