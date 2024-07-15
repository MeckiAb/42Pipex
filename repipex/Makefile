# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: labderra <labderra@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 17:36:27 by labderra          #+#    #+#              #
#    Updated: 2024/07/13 17:39:14 by labderra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
# BONUS = pipex
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a
SRC = main.c 

# SRC_BONUS = main_bonus.c 

CC = clang -Wall -Wextra -Werror -gdwarf-4
OBJ = $(SRC:.c=.o)
# OBJ_BONUS = $(SRC_BONUS:.c=.o)

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

# bonus: $(BONUS)

# $(BONUS) : $(OBJ_BONUS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(OBJ_BONUS) $(LIBFT) $(FT_PRINTF) -o $@

.PHONY : all clean fclean re #bonus