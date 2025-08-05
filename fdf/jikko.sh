#!/bin/bash
set -e  # コケたら即終了

# ./test $(shuf -r -i 0-500 -n 4 | tr "\n" " ")

# --- OS判定とMiniLibX設定 ---
UNAME=$(uname)
if [[ "$UNAME" == "Darwin" ]]; then
    # macOS
    MLX_DIR="minilibx_macos"
    MLX_FLAGS="-framework OpenGL -framework AppKit"
elif [[ "$UNAME" == "Linux" ]]; then
    # Linux (Ubuntu)
    MLX_DIR="minilibx"
    MLX_FLAGS="-lX11 -lXext"
else
	echo "Unsupported OS: $UNAME" >&2
	exit 1
fi

# --- 共通設定 ---
LIBFT_DIR="libft"
LIBFT_A="$LIBFT_DIR/libft.a"
INC="$LIBFT_DIR/includes"
CFLAGS="-Wall -Wextra -Werror -I inc"
OUT="test"
MLX_A="$MLX_DIR/libmlx.a"

# --- 引数パース ---
if [ $# -lt 1 ]; then
    echo "使い方: $0 <src.c ...> [-o 出力ファイル名]" >&2
    exit 1
fi

SRC=()
while [[ $# -gt 0 ]]; do
    case "$1" in
        -o) shift; OUT="$1" ;;
        *)  SRC+=("$1") ;;
    esac
    shift
done

# --- libft をビルド ---
make rebonus -C "$LIBFT_DIR"
make re -C "$MLX_DIR"

# --- コンパイル実行 ---
cc $CFLAGS "${SRC[@]}" "$LIBFT_A" \
    -I"$INC" -I"$MLX_DIR" \
    -L"$MLX_DIR" -lmlx -lm $MLX_FLAGS \
    -o "$OUT"