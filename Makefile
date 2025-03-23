# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/23 00:40:03 by kben-tou          #+#    #+#              #
#    Updated: 2025/03/23 11:08:19 by sait-nac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MANDATORY_DIR = mandatory/
BUILTINS_DIR = $(MANDATORY_DIR)builtins/
EXECUTION_DIR = $(MANDATORY_DIR)execution/
EXPANDING_DIR = $(MANDATORY_DIR)expanding/
PARSING_DIR = $(MANDATORY_DIR)parsing/
UTILS_DIR = $(MANDATORY_DIR)utils/

SRC = $(MANDATORY_DIR)minishell.c

B_SRC = $(addprefix $(BUILTINS_DIR), builtin.c builtin_rideractions.c cd_command.c copy_list.c echo_command.c exit_command.c export_command.c \
		filter_export.c is_builtin.c pwd_command.c unset_command.c update_pwd.c)
ET_SRC = $(addprefix $(EXECUTION_DIR), backup_env.c child_proccess_mangement.c command_handler.c exec_cmd.c get_env.c get_exec_path.c get_path.c \
		her_doc.c her_doc_management.c multiple_command.c ridirections.c run_sing_command.c signals.c)
ED_SRC = $(addprefix $(EXPANDING_DIR), expand_commands.c expand_env_variables.c here_doc_expanding.c expanding_helper.c)
UT_SRC = $(addprefix $(UTILS_DIR), clean_fd.c env_list_utils.c env_to_array.c errors.c find_key.c ft_atoi.c ft_is_digit.c ft_lstlast.c ft_putstr_fd_bonus.c \
		ft_strcmp.c ft_strlcat.c garbag_collector.c her_doc_utils.c libft_utils0.c libft_utils1.c libft_utils2.c libft_utils3.c list_data.c list_size.c \
		list_utils.c normal_split.c split_qoutes.c update_status.c)
P_SRC = $(addprefix $(PARSING_DIR), check_echo_option.c find_data.c parser.c qoutes.c redirections.c tokener.c)

SRCS = $(SRC) $(B_SRC) $(ET_SRC) $(ED_SRC) $(P_SRC) $(UT_SRC)

CFLAGS =  -Wall -Wextra -Werror -fsanitize=address

RLLIB1 = $(shell brew --prefix readline)/lib
RLINC1 = $(shell brew --prefix readline)/include

HEADER = includes/minishell.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I ${RLINC1} -c $< -o $@ -MMD

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L ${RLLIB1} -lreadline

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS:.o=.d) 

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re