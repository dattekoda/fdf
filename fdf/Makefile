# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/06 20:03:40 by khanadat          #+#    #+#              #
#    Updated: 2025/08/06 20:16:00 by khanadat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -I incs
RM = rm -rf

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRCS = srcs/color.c srcs/draw_map.c srcs/free.c \
	srcs/keypress.c srcs/line.c srcs/main.c \
	srcs/map_utils.c srcs/render.c \
	srcs/set.c srcs/validate_map.c

OBJS_DIR = objs
OBJS = $(patsubst srcs/%.c,$(OBJS_DIR)/%.o,$(SRCS))

UNAME = $(shell uname -s)

ifeq ($(UNAME),Darwin)
	MLX_DIR := minilibx_macos
	MLX_FLAGS := -framework OpenGL -framework AppKit
else ifeq ($(UNAME),Linux)
	MLX_DIR := minilibx-linux
	MLX_FLAGS := -lX11 -lXext
else
	$(error Unsupported OS: $(UNAME))
endif

MLX_A = $(MLX_DIR)/libmlx.a

LDFLAGS = -L $(MLX_DIR)
LDLIBS = -lmlx -lm $(MLX_FLAGS) $(LIBFT_A)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(LIBFT_DIR)/includes \
	-I $(MLX_DIR) -c $< -o $@

$(LIBFT_A):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all