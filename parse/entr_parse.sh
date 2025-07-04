#!/bin/bash

SRC=$1
find "$SRC" | entr -rs "cc $SRC ../libft/libft.a && valgrind ./a.out ../fdf/42.fdf"