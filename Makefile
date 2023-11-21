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

SRCS	= 	main.c $(addprefix parsing/, verif_quote.c enum.c structure.c syntax_error.c env.c dollar_quote.c dollar_quote2.c dollar.c dollar2.c structure2.c)\
			$(addprefix pipex/, builtin.c pipex.c here_doc.c here_doc_utils.c free.c parsing.c redirect_fd.c )\
			$(addprefix builtin/src/, echo.c exit.c env.c export.c export_noargs.c pwd.c cd.c cd2.c ft_printf_fd.c unset.c unset_utils.c utils2.c utils.c signals.c sigaction_utils.c)\

OBJS	=	${SRCS:.c=.o}

LIBFT	= libft/libft.a

NAME	= minishell

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3

VMINI	= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes\
					 --suppressions=$(PWD)/minishell.supp

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
			make -C libft
			$(CC) $(OBJS) $(LIBFT) -g -o $(NAME) -lreadline

clean:
				make -C libft clean
				rm -f ${OBJS}

fclean:		clean
				make clean
				rm -f ${NAME} $ $(LIBFT)

re:				fclean all

rlleaks:		$(NAME)
					$(VMINI) ./minishell

.PHONY:			all clean fclean re rlleaks
