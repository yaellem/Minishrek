# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabed <mabed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 16:59:09 by mabed             #+#    #+#              #
#    Updated: 2023/11/09 17:07:46 by mabed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
				ft_tolower.c ft_atoi.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c  ft_strlen.c \
				ft_strchr.c ft_strrchr.c ft_strnstr.c ft_bzero.c ft_memset.c ft_memcmp.c\
				ft_calloc.c ft_strdup.c ft_substr.c ft_memmove.c ft_memcpy.c ft_strtrim.c\
				ft_strjoin.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_memchr.c\
				ft_putnbr_fd.c ft_putendl_fd.c ft_itoa.c get_next_line_utils.c\
				get_next_line.c

OBJS	=	${SRCS:.c=.o}

NAME	= libft.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
				ar rc ${NAME} ${OBJS}
				ranlib ${NAME}

clean:
				rm -f ${OBJS}

fclean:		clean
				rm -f ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
