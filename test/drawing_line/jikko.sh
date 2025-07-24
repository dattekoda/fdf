#!/bin/bash

SRC=$1
cc "$SRC" "../libft/libft.a" "../minilibx/libmlx.a" "../minilibx/libmlx_Linux.a" -lX11 -lXext -lm -o draw