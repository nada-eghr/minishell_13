# Compiler and flags
CC      = gcc -fsanitize=address -g

CFLAGS  = -Wall -Wextra -Werror 
LIBS    = -lreadline

# Source and object files
NAME    = minishell
SRCS    =  expand.c env_utils.c utils1.c cmd.c main.c herdoc.c  get_files.c get_param.c tokenization.c utils.c   listUtils.c check_error.c
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

.PHONY: all clean fclean re
