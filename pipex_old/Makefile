# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: labderra <labderra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 09:26:13 by labderra          #+#    #+#              #
#    Updated: 2024/07/13 10:41:37 by labderra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
# BONUS = pipex
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a
SRC = main.c \
init.c \
execs.c

SRC_BONUS = main_bonus.c \
init_bonus.c \
execs_bonus.c \
heredoc_bonus.c
	
CC = clang -Wall -Wextra -Werror -gdwarf-4
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT) $(FT_PRINTF)
	$(CC) $(OBJ) $(LIBFT) $(FT_PRINTF) -o $@ 

$(LIBFT) : 
	make -C "libft"
	make -C "libft" bonus

$(FT_PRINTF) :
	make -C "ft_printf"

%.o : %.c
	$(CC) -c $< -o $@

clean : 
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	make -C "libft" clean
	make -C "ft_printf" clean

fclean : clean
	rm -f $(NAME)
	rm -f $(BONUS)
	make -C "libft" fclean
	make -C "ft_printf" fclean

re : fclean all

bonus: $(BONUS)

$(BONUS) : $(OBJ_BONUS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(OBJ_BONUS) $(LIBFT) $(FT_PRINTF) -o $@ 

.PHONY : all clean fclean re bonus
