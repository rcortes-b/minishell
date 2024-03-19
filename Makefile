NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = 

OBJS = $(SRCS:.c=.o)

HEAD = includes/minishell.h

LIBFT = libft/libft.a

all : $(NAME)

%.o : %.c Makefile $(HEAD)
	$(CC) $(FLAGS) -c $< -o $@

libs:
	make -C libft

linux:
	make LINUX=1 all

ifndef LINUX

$(NAME): $(OBJS) libs
	$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $(NAME)

else

$(NAME): $(OBJS) libs
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -Llibft -lft

endif

clean :
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re libs linux