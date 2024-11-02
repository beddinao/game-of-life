CC = cc
SRC = $(wildcard src/*.c)
HR = $(wildcard include/*.h)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
FLAGS = -Iinclude -lglfw -L /Users/beddinao/.brew/opt/glfw/lib ./MLX42/build/libmlx42.a
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	FLAGS += -ldl -pthread -lm
endif
ifeq (($UNAME), Darwin)
	FLAGS += -framework Cocoa -framework IOKit
endif

NAME = gof

all: mlx $(NAME)

mlx:
	@cmake -B ./MLX42/build ./MLX42
	@cmake --build ./MLX42/build -j4 

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAGS)

build/%.o: src/%.c $(HR)
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	rm -rf build && rm -rf MLX42/build

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean
