NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRCS = srcs/parse/split.c srcs/parse/count_words.c srcs/parse/split_utils.c  \
srcs/parse/flags.c srcs/parse/parse_utils.c \
srcs/main.c

OBJS = $(SRCS:.c=.o)

HEAD = includes/minishell.h includes/parse.h

LIBFT = libft/libft.a
READLINE = -L$(HOME)/.brew/Cellar/readline/8.2.10/lib -lreadline -lhistory

all : $(NAME)

%.o : %.c Makefile $(HEAD)
	$(CC) $(FLAGS) -c $< -o $@

libs:
	make -C libft

linux:
	make LINUX=1 all

ifndef LINUX

$(NAME): $(OBJS) libs
	$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $(NAME) $(READLINE)

else

$(NAME): $(OBJS) libs
	$(CC) $(FLAGS) $(READLINE) $(OBJS) -o $(NAME) -Llibft -lft

endif

clean :
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re libs linux