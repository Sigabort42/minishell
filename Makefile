#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/12 15:54:14 by elbenkri          #+#    #+#              #
#    Updated: 2018/03/23 02:13:32 by elbenkri         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	minishell

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	ft_set_unset_env.c \
			ft_utils.c \
			ft_cd.c \
			ft_echo_env_exit.c \
			ft_init_exec.c \
			main.c

OBJS	=	$(SRCS:.c=.o)

LIB	=	libft/libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

clean:
	@make -C libft/ clean
	@/bin/rm -rf $(OBJS)

fclean:	clean
	@make  -C libft/ fclean
	@/bin/rm -rf $(NAME)

re:	fclean all