# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 21:19:51 by vsozonof          #+#    #+#              #
#    Updated: 2024/01/28 22:04:47 by vsozonof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
AR = ar crs
RM = rm -f

BL=\033[1;34m
GR=\033[1;32m
OR=\033[1;33m
RD=\033[1;31m
WH=\033[0m

SRCS = 	srcs/bool_functions/ft_isalpha.c\
		srcs/bool_functions/ft_isdigit.c\
		srcs/bool_functions/ft_isalnum.c\
		srcs/bool_functions/ft_isascii.c\
		srcs/bool_functions/ft_isprint.c\
		srcs/bool_functions/ft_int_overflow_checker.c \
		srcs/bool_functions/ft_is_str_digit.c \
		srcs/bool_functions/ft_is_whitespace.c \
		srcs/bool_functions/ft_isminus.c \
		srcs/str_functions/ft_toupper.c\
		srcs/str_functions/ft_tolower.c\
		srcs/str_functions/ft_striteri.c\
		srcs/str_functions/ft_strmapi.c\
		srcs/str_functions/ft_substr.c\
		srcs/str_functions/ft_strjoin.c\
		srcs/str_functions/ft_strjoin_free.c\
		srcs/str_functions/ft_strtrim.c\
		srcs/str_functions/ft_split.c\
		srcs/str_functions/ft_atol.c \
		srcs/str_functions/ft_split_free.c \
		srcs/str_functions/ft_strlen.c \
		srcs/str_functions/ft_itoa.c\
		srcs/str_functions/ft_atoi.c\
		srcs/str_functions/ft_strchr.c\
		srcs/str_functions/ft_strrchr.c\
		srcs/str_functions/ft_strnstr.c\
		srcs/str_functions/ft_strncmp.c\
		srcs/str_functions/ft_strlen.c\
		srcs/str_functions/ft_strlcpy.c\
		srcs/str_functions/ft_strlcat.c\
		srcs/str_functions/ft_strdup.c\
		srcs/str_functions/gnl.c \
		srcs/str_functions/gnl_utils.c \
		srcs/list_functions/ft_lstnew.c\
		srcs/list_functions/ft_lstsize.c\
		srcs/list_functions/ft_lstlast.c\
		srcs/list_functions/ft_lstadd_front.c\
		srcs/list_functions/ft_lstadd_back.c\
		srcs/list_functions/ft_lstdelone.c\
		srcs/list_functions/ft_lstiter.c\
		srcs/list_functions/ft_lstclear.c\
		srcs/list_functions/ft_lstmap.c\
		srcs/list_functions/ft_add_at.c \
	   	srcs/list_functions/ft_set_at.c \
	   	srcs/list_functions/ft_create_cell.c \
	   	srcs/list_functions/ft_get_at.c \
	   	srcs/list_functions/ft_free_at.c \
	   	srcs/list_functions/ft_free_list.c \
	   	srcs/list_functions/ft_lstlen.c \
	   	srcs/list_functions/ft_printlist.c \
		srcs/list_functions/ft_add_prev_ptr.c \
		srcs/writing_functions/ft_putchar_fd.c\
		srcs/writing_functions/ft_putnbr_fd.c\
		srcs/writing_functions/ft_putstr_fd.c\
		srcs/writing_functions/ft_putendl_fd.c\
		srcs/writing_functions/ft_putstr.c \
		srcs/writing_functions/ft_putnbr.c \
		srcs/writing_functions/ft_putnbr_hexa.c \
		srcs/writing_functions/ft_pointer_handler.c \
		srcs/writing_functions/ft_printf.c \
		srcs/writing_functions/ft_error_writer.c \
		srcs/memory_functions/ft_memcpy.c\
		srcs/memory_functions/ft_memset.c\
		srcs/memory_functions/ft_memmove.c\
		srcs/memory_functions/ft_memchr.c\
		srcs/memory_functions/ft_memcmp.c\
		srcs/memory_functions/ft_bzero.c\
		srcs/memory_functions/ft_calloc.c\
		
OBJS = $(SRCS:.c=.o)

all: $(OBJS) $(NAME)


$(NAME): $(OBJS) $(HEADER)
	@echo "\n$(RD)LIBFT -$(WH)$(BL)\tBuilding library.$(WH)"
	@$(AR) $@ $^
	@echo "$(RD)LIBFT -$(WH)$(BL)\tLibrary built successfully.$(WH)"

%.o: %.c
	@echo "$(RD)LIBFT -\t$(WH)$(BL)Compiling $(OR)($<)$(WH)\c\r"
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "                                   \r\c" 
     
     
clean:
		@$(RM) $(OBJS) 
		@echo "$(RD)LIBFT -\t$(WH)$(GR)All .o files were deleted !$(WH)"

fclean: 
		@$(RM) $(NAME) $(OBJS)
		@echo "$(RD)LIBFT -\t$(WH)$(GR)All .o files and binaries were deleted !$(WH)"


re: fclean all

.PHONY: all clean fclean re
