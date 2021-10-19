# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artmende <artmende@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/16 16:01:43 by artmende          #+#    #+#              #
#    Updated: 2021/10/16 17:52:41 by artmende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS_CLIENT =	./client.c \
				./call_exit.c \

SRCS_SERVER =	./server.c

SRCS_LIBFT =	./from_libft/ft_atoi.c \
				./from_libft/ft_calloc.c \
				./from_libft/ft_memset.c \
				./from_libft/ft_putnbr_fd.c \
				./from_libft/ft_strlen.c \

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o) $(OBJS_LIBFT)

OBJS_SERVER = $(SRCS_SERVER:.c=.o) $(OBJS_LIBFT)

OBJS_LIBFT = $(SRCS_LIBFT:.c=.o)

RM = rm -f

NAME_CLIENT = client

NAME_SERVER = server

all : $(NAME_CLIENT) $(NAME_SERVER)

bonus : all

$(NAME_CLIENT) : $(OBJS_CLIENT)
	$(CC) -o $(NAME_CLIENT) $(CFLAGS) $(OBJS_CLIENT)

$(NAME_SERVER) : $(OBJS_SERVER)
	$(CC) -o $(NAME_SERVER) $(CFLAGS) $(OBJS_SERVER)

clean :
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)

fclean : clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re : fclean all

.PHONY : all bonus clean fclean re
