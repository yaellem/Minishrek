# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 15:02:24 by mabed             #+#    #+#              #
#    Updated: 2023/11/21 15:09:16 by cabouzir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PWD = `pwd`

INCS_DIR	= incs/*
LIBFT_INCS_DIR 		= $(dir $(LIBFT))

SRC	= 	main.c \
		$(addprefix parsing/, verif_quote.c enum.c structure.c syntax_error.c env.c dollar_quote.c dollar_quote2.c dollar.c dollar2.c structure2.c)\
		$(addprefix pipex/, builtin.c pipex.c here_doc.c here_doc_utils.c free.c parsing.c redirect_fd.c )\
		$(addprefix builtin/src/, echo.c exit.c env.c export.c export_noargs.c pwd.c cd.c cd2.c ft_printf_fd.c unset.c unset_utils.c utils2.c utils.c signals.c sigaction_utils.c)\

SRC_DIR		= ./srcs/
OBJ_DIR    = ./.objs/

OBJS		=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
SRCS     :=  $(addprefix $(SRC_DIR), $(SRC))

LIBFT	= libft/libft.a

NAME	= minishell

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3 -I$(INCS) -I$(LIBFT_INCS_DIR)

VMINI	= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes\
					 --suppressions=$(PWD)/minishell.supp

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME): $(OBJ_DIR) $(OBJS) $(INCS) Makefile
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -g -o $(NAME) -lreadline


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	@echo "\033[0;32m[✓]\033[0m\033[0;33m [Minishell] Compiling : \033[0m" $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/builtin/src
	@mkdir -p $(OBJ_DIR)/pipex


clean:
	make -C libft clean
	rm -rf ${OBJ_DIR}
	rm -rf $(OBJ_DIR)/parsing
	rm -rf $(OBJ_DIR)/builtin/src
	rm -rf $(OBJ_DIR)/pipex

fclean:		clean
				make clean
				rm -f ${NAME} $ $(LIBFT)

re:				fclean all

rlleaks:		$(NAME)
					$(VMINI) ./minishell

.PHONY:			all clean fclean re rlleaks
