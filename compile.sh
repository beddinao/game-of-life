#!/bin/bash

#cd lib/MLX42/

#cmake -B build 
#cmake --build build -j4

#cd -

gcc main.c -o gof -framework Cocoa -framework IOKit ./MLX42/build/libmlx42.a \
	-Iinclude -lglfw -L /Users/beddinao/.brew/opt/glfw/lib  # -g -fsanitize=address

