# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vquesnel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/26 13:35:37 by vquesnel          #+#    #+#              #
#*   Updated: 2016/05/01 15:49:05 by vquesnel         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME= fdf

SRCS= srcs/main.c \
	srcs/init_env.c \
	srcs/get_map.c \
	srcs/init_node.c

OBJS= $(SRCS:.c=.o)
INCLUDES= -I libft -I includes -I mlx/
LIBS= -L libft/ -lft -L mlx/ -lmlx -lm
FLAGS= -Wall -Wextra -Werror -g
FRAMEWORK= -framework AppKit -framework OpenGL

$(NAME):	$(OBJS)
	@make -C libft/
	@make -C mlx/
	@gcc -o $(NAME) $(OBJS) $(LIBS) $(FRAMEWORK)
	@echo "		\033[31;1m"
	@echo "		  ,__________,  ,_________,       "
	@echo "		  |          |  |         |      "
	@echo "		  |____      |  |____     |      "
	@echo "		       /    /       /    /        "
	@echo "		      /    /       /    /          "
	@echo "		     /    /       /    /          "
	@echo "		    /    /       /    /           "
	@echo "		   /    /       /    /            "
	@echo "		   ____         ____              "
	@echo "\033[0m"
	@echo "		  ALL_IS_WORKING_MAN                "
	@echo "\n"


$(OBJS): %.o: %.c
	@gcc $(FLAGS) $(INCLUDES) -c $< -o $@

all:	$(NAME)

clean:
	@make -C libft/ clean
	@make -C mlx/ clean
	@rm -f $(OBJS)
	@echo "\033[37mall fdf_files.o have been deleted\033[0m"

fclean:	clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@echo "\033[31m$(NAME) has been deleted\033[0m"

re:		fclean all

.PHONY: all clean fclean re

