M = mandatory
U = utils
B = builtins
ET = execution
ED = expanding
P = parsing
NAME = minishell 

FILS = $(wildcard $(M)/$(U)/*.c) \
		$(wildcard $(M)/$(ET)/*.c) \
		$(wildcard $(M)/$(B)/*.c)\
		$(wildcard $(M)/$(P)/*.c)\
		$(wildcard $(M)/$(ED)/*.c)\
		$(wildcard $(M)/*.c) 

CFLAGS =  -Wall -Wextra -Werror -g #-fsanitize=address
REDLINE = -lreadline -lncurses
OBJS = 	$(FILS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) $(REDLINE) -o $@

clean:
	rm -rf $(OBJS) 

fclean: clean
	rm -rf $(NAME)

re: fclean all
