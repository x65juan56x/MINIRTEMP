NAME		:= miniRT
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

INCS_DIR	:= include
SRCS		:= main.c
OBJS		:= $(SRCS:.c=.o)

# MLX42 (GLFW) configuration
# By default we expect headers in ./MLX42/include and lib in ./MLX42/build
# Override with:
#   make MLX42_INC=/path/to/MLX42/include MLX42_LIB=/path/to/MLX42/build
MLX42_INC	?= MLX42/include
MLX42_LIB	?= MLX42/build
MLX42_FLAGS := -L$(MLX42_LIB) -lmlx42 -ldl -lglfw -lm -lpthread

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX42_INC) $^ -o $@ $(MLX42_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX42_INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all
