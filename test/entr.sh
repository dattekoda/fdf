#!/bin/bash

SRC=$1
find "$SRC" | entr -rs "cc \"$SRC\" \"../libft/libft.a\" \"../minilibx/libmlx_Linux.a\" -lX11 -lXext -lm -o test && ./test ../fdf/42.fdf"