// Ventana mínima usando MLX42 (GLFW/OpenGL)
// Ajusta MLX42_INC/MLX42_LIB en el Makefile si tu instalación difiere.

#include "include/minirt.h"
#include "MLX42/MLX42.h"
#include <stdio.h>

typedef struct s_mlx_ctx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
} t_mlx_ctx;

static void on_key(mlx_key_data_t keydata, void *param)
{
	t_mlx_ctx *mlx_ctx;

	mlx_ctx = (t_mlx_ctx*)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx_ctx->mlx);
}

static void clear_image(mlx_image_t *img, uint32_t color)
{
	uint32_t	*pixels;
	size_t		count;
	size_t		i;

	pixels = (uint32_t*)img->pixels;
	count = (size_t)img->width * (size_t)img->height;
	i = -1;
	while (++i < count)
		pixels[i] = color;
}

int main(int argc, char **argv)
{
	(void)argc; (void)argv;

	t_mlx_ctx mlx_ctx = {0};
	mlx_ctx.mlx = mlx_init(WIN_W, WIN_H, "miniRT", false);
	if (!mlx_ctx.mlx)
		return (write(2, "Error\nmlx_init failed\n", 20), 1);
	mlx_ctx.img = mlx_new_image(mlx_ctx.mlx, WIN_W, WIN_H);
	if (!mlx_ctx.img)
		return (write(2, "Error\nimage creation failed\n", 28), 1);
	if (mlx_image_to_window(mlx_ctx.mlx, mlx_ctx.img, 0, 0) < 0)
		return (write(2, "Error\nimage to window failed\n", 30), 1);
	clear_image(mlx_ctx.img, 0x000000FF);
	mlx_key_hook(mlx_ctx.mlx, on_key, &mlx_ctx);
	mlx_close_hook(mlx_ctx.mlx, (mlx_closefunc)NULL, NULL); // opcional
	mlx_loop(mlx_ctx.mlx);
	mlx_terminate(mlx_ctx.mlx);
	return 0;
}
