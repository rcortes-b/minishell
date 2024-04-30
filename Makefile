NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRCS = srcs/parse/split.c srcs/parse/split_utils.c srcs/parse/environment.c  srcs/parse/environment_utils.c\
srcs/parse/order.c srcs/parse/parse_utils.c \
srcs/parse/categorization.c  srcs/parse/tokenization.c \
srcs/checker/checker.c \
srcs/builtins/echo.c srcs/builtins/env.c srcs/builtins/export.c srcs/builtins/empty_export.c srcs/builtins/builtins_utils.c \
srcs/builtins/unset.c  srcs/builtins/exit.c srcs/builtins/pwd.c srcs/builtins/chdir.c srcs/builtins/export_utils.c \
srcs/error_handler/parse_errors.c srcs/error_handler/parse_errors2.c \
srcs/exec/exec.c srcs/exec/cooking_execution.c srcs/exec/exec_utils.c srcs/exec/files_utils.c \
srcs/exec/heredoc.c srcs/exec/files.c srcs/exec/signal.c srcs/exec/exec_builtins.c \
srcs/main.c \
srcs/expander/mod_split.c srcs/expander/expander_split.c srcs/expander/expander_aux.c \
srcs/expander/expander.c srcs/expander/expander_utils.c srcs/expander/remove_quotes.c \
srcs/expander/expander_utils2.c srcs/expander/remove_quotes2.c srcs/expander/quotes_utils.c \
srcs/expander/quotes_utils2.c srcs/expander/utils.c srcs/expander/expander_utils3.c\

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

HEAD = includes/minishell.h includes/parse.h includes/builtins.h includes/checker.h includes/expander.h includes/exec.h

LIBFT = libft/libft.a
READLINE = -L$(HOME)/.brew/Cellar/readline/8.2.10/lib -lreadline -lhistory

all : make_libs $(NAME)

%.o : %.c Makefile $(HEAD)
	$(CC) $(FLAGS) -MMD -c $< -o $@

make_libs:
	make -C libft

linux:
	make LINUX=1 all

ifndef LINUX

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $(NAME) $(READLINE)

else

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(READLINE) $(OBJS) -o $(NAME) -Llibft -lft

endif

clean :
	make clean -C libft
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean re libs linux
