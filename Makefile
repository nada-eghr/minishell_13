# Compiler and flags
CC      = gcc -fsanitize=address -g

CFLAGS  = -Wall -Wextra -Werror 
LIBS    = -lreadline

# Source and object files
NAME    = minishell
SRCS    =  ./pars/expand.c  ./pars/utils1.c  ./pars/utils.c \
./pars/cmd.c main.c ./pars/herdoc.c  ./pars/get_files.c ./pars/get_param.c ./pars/tokenization.c \
./pars/listUtils.c ./pars/check_error.c \
./exec/small_libft.c ./exec/exc.c ./exec/helper.c ./exec/free_fun.c ./exec/linkd_list.c ./exec/all_env.c \
./exec/bilt_in/pwd.c ./exec/bilt_in/env.c ./exec/bilt_in/cd.c ./exec/bilt_in/unset.c ./exec/bilt_in/export.c ./exec/bilt_in/exit.c ./exec/bilt_in/echo.c \
 ./exec/ignor_fun_now.c ./exec/rediraction.c
OBJS    = $(SRCS:.c=.o)

# Build target
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

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
