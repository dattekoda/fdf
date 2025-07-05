#!/bin/bash

SRC=$1
find "$SRC" | entr -rs "cc $SRC ../libft/libft.a && valgrind --leak-check=full --track-origins=yes ./a.out ../fdf/42.fdf"