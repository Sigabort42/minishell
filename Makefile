NAME	=	minishell

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror #-g3 -fsanitize=address

SRCS	=	main.c \

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