# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/21 10:59:33 by rstrub            #+#    #+#              #
#    Updated: 2024/05/27 07:28:51 by ertupop          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS  = ft_printf.c ft_putchar.c ft_puthexa.c ft_putnbr.c ft_putstr.c ft_putunsign.c ft_putvoid.c

OBJS  = ${SRCS:.c=.o}
NAME  = libftprintf.a
HEADER = ft_printf.h
.c.o:
	cc -Wall -Wextra -Werror -g -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS} ${HEADER}
			@ar rcs ${NAME} ${OBJS}

clean:
			@rm -f ${OBJS}

fclean:		clean
			@rm -f ${NAME}

re:			fclean ${NAME}

.PHONY:		re clean fclean all
