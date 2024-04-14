NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
#SRCS_ALL = ${addprefix "srcs", $(SRCS)}

SRCS = srcs/parse/split.c srcs/parse/split_utils.c srcs/parse/environment.c  srcs/parse/environment_utils.c\
srcs/parse/order.c srcs/parse/parse_utils.c \
srcs/parse/categorization.c  srcs/parse/tokenization.c \
srcs/checker/checker.c \
srcs/expander/expander.c srcs/expander/expander_utils.c srcs/expander/expander_utils2.c \
srcs/builtins/echo.c srcs/builtins/env.c srcs/builtins/export.c srcs/builtins/empty_export.c \
srcs/builtins/unset.c  srcs/builtins/exit.c srcs/builtins/pwd.c \
srcs/error_handler/parse_errors.c srcs/error_handler/parse_errors2.c \
srcs/exec/exec.c srcs/exec/cooking_execution.c srcs/exec/exe_cmd.c \
srcs/exec/builtins_exe.c srcs/exec/heredoc.c srcs/exec/redirects.c \
srcs/main.c

OBJS = $(SRCS:.c=.o)

HEAD = includes/minishell.h includes/parse.h includes/builtins.h includes/checker.h includes/expander.h includes/exec.h

LIBFT = libft/libft.a
READLINE = -L$(HOME)/.brew/Cellar/readline/8.2.10/lib -lreadline -lhistory

all : $(NAME)

%.o : %.c Makefile $(HEAD)
	$(CC) $(FLAGS) -c $< -o $@

libs:
	make bonus -C libft

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