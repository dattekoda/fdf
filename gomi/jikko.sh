#!/bin/bash
set -e                           # コケたら即終了

# --- 設定 ---
MLX_DIR="../minilibx_mac"        # MiniLibX のパス
LIBFT_A="../libft/libft.a"       # libft.a のパス
INC="../libft/includes"          # libft ヘッダ
CFLAGS="-Wall -Wextra -Werror"   # お好みの警告オプション
OUT="test"                       # デフォルト出力名

# --- 引数パース ---
if [ $# -lt 1 ]; then
    echo "使い方: $0 <src.c ...> [-o 出力ファイル名]" >&2
    exit 1
fi

SRC=()                           # ソースをここに溜める
while [[ $# -gt 0 ]]; do
    case "$1" in
        -o)  shift; OUT="$1" ;;  # -o filename で任意の出力名
        *)   SRC+=("$1") ;;
    esac
    shift
done

# --- コンパイル ---
cc $CFLAGS "${SRC[@]}" "$LIBFT_A" \
   -I"$INC" -I"$MLX_DIR" \
   -L"$MLX_DIR" -lmlx -lm \
   -framework OpenGL -framework AppKit \
   -o "$OUT"
