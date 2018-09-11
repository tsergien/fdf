# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsergien <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/13 18:09:20 by tsergien          #+#    #+#              #
#    Updated: 2018/09/10 19:34:50 by tsergien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_FILES = main.c reading.c wu_line.c grid.c wu_additional.c rotate.c keys.c\
			drawing_stuff.c errors.c mouse.c keys_func.c set_func.c rgb.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC_DIR = src/

OBJ_DIR = obj/

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

HEADER = -I /usr/local/include -I includes/

FRAME = -L /usr/local/lib/ -lmlx -framework OpenGl -framework AppKit -lm

WWW = -Wall -Wextra -Werror

LIB_DIR = libft/

COLOR = \x1b[38;5;62m

RESET_COLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR)
	@cc $(OBJ) -o $(NAME) $(HEADER) $(FRAME) -L $(LIB_DIR) -lft
	@echo "$(COLOR)***		fdf compiled		***$(RESET_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@gcc $(WWW) -o $@ -c $< $(HEADER)

clean:
	@make clean -C $(LIB_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR)***		obj cleaned		***$(RESET_COLOR)"

fclean: clean
	@make fclean -C $(LIB_DIR)
	@rm -f $(NAME)
	@echo "$(COLOR)***		crystall clean		***$(RESET_COLOR)"

norm:
	@norminette $(SRC) includes/*.h 

re: fclean all
