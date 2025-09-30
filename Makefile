NAME		:= miniRT
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror

INCS_DIR	:= include
LIBFT_DIR	:= Libft
LIBFT_A		:= $(LIBFT_DIR)/libft.a
SRCS		:= main.c \
			src/color.c \
			src/vec3.c \
			src/ray.c \
			src/renderer.c \
			src/scene.c \
			src/parser.c \
			src/parser_utils.c \

OBJS		:= $(SRCS:.c=.o)

MLX42_INC	?= MLX42/include
MLX42_LIB	?= MLX42/build
MLX42_FLAGS := -L$(MLX42_LIB) -lmlx42 -ldl -lglfw -lm -lpthread

.PHONY: all clean fclean re bonus

all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX42_INC) $^ -o $@ $(MLX42_FLAGS) $(LIBFT_A)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX42_INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean || true

re: fclean all

bonus: all

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR) all

# --- Parser test (no ventana) ---
PARSER_SRCS := src/parser_main.c \
			src/scene.c \
			src/parser.c \
			src/parser_utils.c \
			src/vec3.c \
			src/color.c
PARSER_OBJS := $(PARSER_SRCS:.c=.o)

parser_test: $(PARSER_OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -I$(INCS_DIR) $^ -o $@ -lm $(LIBFT_A)

parser_clean:
	rm -f $(PARSER_OBJS) parser_test

# Run all parser tests with expected outcomes
parser_tests: parser_test
	@set -e; \
	pass=0; fail=0; \
	echo "[parser_tests] Running..."; \
	for f in tests/scenes/valid01.rt tests/scenes/whitespace_comments.rt; do \
	  if ./parser_test $$f >/dev/null; then echo "PASS $$f"; pass=$$((pass+1)); else echo "FAIL $$f"; fail=$$((fail+1)); fi; \
	done; \
	for f in tests/scenes/invalid01.rt tests/scenes/missing_A.rt tests/scenes/missing_C.rt tests/scenes/missing_L.rt tests/scenes/bad_color.rt tests/scenes/bad_fov.rt tests/scenes/unknown_id.rt; do \
	  if ./parser_test $$f >/dev/null; then echo "FAIL $$f (should error)"; fail=$$((fail+1)); else echo "PASS $$f (error)"; pass=$$((pass+1)); fi; \
	done; \
	echo "[parser_tests] PASS=$$pass FAIL=$$fail"; \
	if [ $$fail -ne 0 ]; then exit 1; fi
