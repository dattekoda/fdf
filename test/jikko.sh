#!/bin/bash

SRC=$1
if [ "$(uname -s)" == "Darwin" ] ; then
	cc "$SRC" "../minilibx/libmlx_mac.a" "../minilibx/libmlx_Darwin.a" -lX11 -lXext
fi
if [ "$(uname -s)" == "Linux" ] ; then
	cc "$SRC" "../minilibx/libmlx.a" "../minilibx/libmlx_Linux.a" -lX11 -lXext
fi