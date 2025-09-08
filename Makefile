NAME		:= miniRT
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

INCS_DIR	:= include
SRCS		:= main.c \
			src/color.c \
			src/vec3.c \
			src/ray.c \
			src/renderer.c

OBJS		:= $(SRCS:.c=.o)

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
