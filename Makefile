# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 16:28:49 by sgoldenb          #+#    #+#              #
#    Updated: 2024/05/11 14:57:20 by sgoldenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include includes/libft/custom.mk

MAKEFLAGS += --silent

NAME = fractol
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -O3
LDFLAGS = -Lincludes/libft -Lincludes/minilibx-linux
LIBS = -lft -lmlx_Linux -lXext -lX11 -lm -lz

SRC_DIR = src
INC_DIR = includes

SRCS = julia_utils.c draw.c fractals.c graphics.c fractol.c data.c hooks.c utils.c key_actions.c mouse_hooks.c
OBJS = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

debug: mlx libft $(OBJS)
	@echo "\n$(INFO_MESSAGE)Compilation fractol"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) includes/minilibx-linux/libmlx.a $(LDFLAGS) $(LIBS) || { echo "$(ERROR_MESSAGE)Erreur de compilation fractol"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)FRACTOL OK\n"

$(NAME): norminette mlx libft $(OBJS)
	@echo "\n$(INFO_MESSAGE)Compilation fractol"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) includes/minilibx-linux/libmlx.a $(LDFLAGS) $(LIBS) || { echo "$(ERROR_MESSAGE)Erreur de compilation fractol"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)FRACTOL OK\n"

%.o: %.c
	@if [ -z "$?" ]; then \
		echo "$(INFO_MESSAGE)Fichiers sources identiques, aucun changement."; \
		exit $?; \
	else \
		echo "\t$<"; \
		$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@ || { echo "\t$(COMP_KO)"; exit $?; }; \
		echo "\t$(COMP_OK)"; \
	fi

norminette:
	norminette $(SRC_DIR)
	norminette $(INC_DIR)/libft
	norminette $(INC_DIR)/fractol.h $(INC_DIR)/colors.h $(INC_DIR)/keycodes.h
	@echo "$(SUCCESS_MESSAGE)NORME OK\n"

mlx:
	@echo "$(INFO_MESSAGE)Compilation MLX"
	make -C $(INC_DIR)/minilibx-linux 2>/dev/null || { echo "$(ERROR_MESSAGE)Erreur de compilation MLX"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)MLX OK\n"

libft:
	@echo "$(INFO_MESSAGE)Compilation libft"
	make all -C includes/libft 2>/dev/null || { echo "$(ERROR_MESSAGE)Erreur de compilation LIBFT"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)LIBFT OK\n"

clean:
	@echo "$(INFO_MESSAGE)Nettoyage des objets"
	rm -f $(OBJS) || $(ERROR_EXIT) "Erreur lors du nettoyage objet"
	make clean -C includes/libft 2>/dev/null || { echo "$(ERROR_MESSAGE)Erreur lors du nettoyage objet"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)Nettoyage objets OK\n"

fclean:
	@echo "$(INFO_MESSAGE)Nettoyage programmes & librairies"
	rm -f $(NAME) || $(ERROR_EXIT) "Erreur lors du nettoyage programme"
	make fclean -C includes/libft || { echo "$(ERROR_MESSAGE)Erreur lors du nettoyage des librairies"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)Nettoyage programmes & librairies OK\n"

re: clean all

.PHONY: all fclean clean
.DEFAULT_GOAL = all