/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:59:39 by ertupop           #+#    #+#             */
/*   Updated: 2021/12/26 11:00:03 by ertupop          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_printf(const char *string, ...);
int	ft_putchar(int c);
int	ft_putstr(char *s);
int	ft_putnbr(int c);
int	ft_puthexa(unsigned int nbr, char *base);
int	ft_putunsign(unsigned int nbr);
int	ft_putvoid(unsigned long long n);

#endif
