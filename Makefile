# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ertupop <ertupop@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 23:22:06 by vsozonof          #+#    #+#              #
#    Updated: 2024/06/10 09:53:49 by ertupop          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -g3

BL=\033[1;34m
GR=\033[1;32m
OR=\033[1;33m
RD=\033[1;31m
WH=\033[0m

SRCS_LIB = libft/libft.a \

SRCS = main.c \
	   parsing/init/init_master.c \
	   parsing/init/alloc_utils-1.c \
	   parsing/input_parser.c \
	   parsing/lexer/format_node.c \
	   parsing/lexer/input_splitter.c \
	   parsing/lexer/single_node.c \
	   parsing/lexer/multi_node.c \
	   parsing/lexer/splitted_input_identifier.c \
	   parsing/utils/counters.c \
	   parsing/utils/counters-2.c \
	   parsing/utils/bool_utils-1.c \
	   parsing/utils/bool_utils-2.c \
	   parsing/utils/pipe_splitter.c \
	   parsing/utils/heredoc.c \
	   parsing/errors/syntax_errors.c \
	   parsing/errors/pipe_errors.c \
	   parsing/errors/exit_status.c \
	   parsing/errors/redir_syntax_error.c \
	   parsing/expand/expand_master.c \
	   parsing/expand/expand_utils-0.c \
	   parsing/expand/expand_utils-1.c \
	   parsing/expand/expand_utils-2.c \
	   parsing/env/env_utils-1.c \
	   parsing/env/env_utils-2.c \
	   free/free_master.c \
	   free/free_utils-1.c \
	   signal/signal_master.c \

SRCS	+=	$(addprefix bultins/, \
			cd.c \
			echo.c \
			env.c \
			exit.c \
			export.c \
			export2.c\
			pwd.c \
			unset.c)

SRCS	+= $(addprefix exec/SRC/, \
			exec_one.c \
			exec_one2.c \
			exec_pipe.c \
			exec_pipe2.c \
			exec0.c \
			exec.c \
			exec2.c \
			exec_ft_command.c \
			exec_utils.c \
			exev_pars.c)

# SRCS	+=	$(addprefix garbage_collector/, \
# 			garbage_2.c \
# 			garbage.c \
# 			gc_garbage.c \
# 			gc_utils.c)

SRCS	+=	$(addprefix utils/, \
			env_utils.c \
			list_utils.c \
			utils_bultins.c \
			utils.c)

# SRCS	+=	$(addprefix Bridge/, \
# 			bridge.c \
# 			bridge_error.c)

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: init $(NAME)

$(NAME): $(OBJS)
	@echo "\n$(RD)MINISHELL -\t$(WH)$(BL)Linking $(OR)($<)$(WH)\r"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline $(SRCS_LIB)
	@echo "                                   \r\c"

%.o: %.c
	@echo "$(RD)MINISHELL -\t$(WH)$(BL)Compiling $(OR)($<)$(WH)\c\r"
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "                                   \r\c"

init:
	make all -C ./libft

clean:
		make clean -C ./libft
		@$(RM) $(OBJS)
		@echo "$(RD)MINISHELL -\t$(WH)$(GR)All .o files were deleted !$(WH)"

fclean: 
		make fclean -C ./libft
		@$(RM) $(NAME) $(OBJS)
		@echo "$(RD)MINISHELL -\t$(WH)$(GR)All .o files and binaries were deleted !$(WH)"

re: fclean all

.PHONY: all clean fclean re init