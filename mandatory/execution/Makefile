# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 16:26:54 by sait-nac          #+#    #+#              #
#    Updated: 2025/01/10 14:50:45 by sait-nac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS = mandat/pipex.c \
       mandat/ft_strjoin.c \
       mandat/ft_split.c \
       mandat/ft_substr.c \
       mandat/ft_strchr.c \
       mandat/pipex_utiles1.c\
       mandat/pipex_utiles2.c

SRCS_BONUS = bonus/ft_putstr_fd_bonus.c \
             bonus/ft_split_bonus.c \
             bonus/ft_strchr_bonus.c \
             bonus/ft_strjoin_bonus.c \
             bonus/ft_substr_bonus.c \
             bonus/get_next_line_bonus.c \
             bonus/pipex_bonus.c \
             bonus/pipex_bonus_utils1.c \
             bonus/pipex_bonus_utils2.c

OBJS = $(SRCS:.c=.o)

BOBJS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

mandat/%.o: mandat/%.c mandat/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS): $(BOBJS)
	$(CC) $(CFLAGS) $(BOBJS) -o $(NAME_BONUS)

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

