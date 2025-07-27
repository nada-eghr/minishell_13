# Compiler and flags
# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I/Users/slamhaou/.brew/opt/readline/include
LDFLAGS = -L/Users/slamhaou/.brew/opt/readline/lib
LIBS    = -lreadline

# Source and object files
NAME    = minishell
SRCS    =  ./pars/expand.c  \
			./pars/utils1.c  \
			./pars/utils.c \
			./pars/pars.c \
			./pars/get_value.c \
			./pars/expand1.c \
			./pars/cmd.c main.c \
			./pars/check_error2.c  \
			./pars/filter_token.c  \
			./pars/get_files.c \
			./pars/get_param.c \
			./pars/tokenization.c \
			./pars/second_tokinization.c \
			./pars/lst_utils1.c \
			./pars/listUtils.c \
			./pars/check_error.c \
			./pars/expand_utils.c \
			./pars/quotes.c \
			./exec/gt_l.c \
			./exec/small_libft.c ./exec/exc.c ./exec/helper.c ./exec/free_fun.c ./exec/linkd_list.c ./exec/all_env.c \
			./exec/bilt_in/pwd.c ./exec/bilt_in/env.c ./exec/bilt_in/cd.c ./exec/bilt_in/unset.c ./exec/bilt_in/export.c ./exec/bilt_in/exit.c ./exec/bilt_in/echo.c \
			./exec/ignor_fun_now.c ./exec/rediraction.c ./exec/path.c ./exec/cmd_herdoc.c ./exec/child.c
OBJS    = $(SRCS:.c=.o)

# Build target
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and binary
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all
s : all clean
.PHONY: all clean fclean re
