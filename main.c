#include "include/minirt.h"

typedef struct s_mrt_ctx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
} t_mrt_ctx;

static void on_key(mlx_key_data_t keydata, void *param)
{
	t_mrt_ctx *mrt_ctx;

	mrt_ctx = (t_mrt_ctx*)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mrt_ctx->mlx);
}

// static void clear_image(mlx_image_t *img, uint32_t color)
// {
// 	uint32_t	*pixels;
// 	size_t		count;
// 	size_t		i;

// 	pixels = (uint32_t*)img->pixels;
// 	count = (size_t)img->width * (size_t)img->height;
// 	i = -1;
// 	while (++i < count)
// 		pixels[i] = color;
// }

static inline void put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if ((unsigned)x >= img->width || (unsigned)y >= img->height)
		return;
	((uint32_t*)img->pixels)[(size_t)y * img->width + (size_t)x] = color;
}

static void draw_test_gradient(mlx_image_t *img)
{
	for (int y = 0; y < (int)img->height; ++y)
	{
		for (int x = 0; x < (int)img->width; ++x)
		{
			uint8_t r = (uint8_t)(255.0f * (float)x / (float)(img->width - 1));
			uint8_t g = (uint8_t)(255.0f * (float)y / (float)(img->height - 1));
			uint8_t b = 64; // constante para diferenciar canales
			put_pixel(img, x, y, rgba_u32(r, g, b, 255));
		}
	}
}

int main(int argc, char **argv)
{
	(void)argc; (void)argv;

	t_mrt_ctx mrt_ctx = {0};
	mrt_ctx.mlx = mlx_init(WIN_W, WIN_H, "miniRT", false);
	if (!mrt_ctx.mlx)
		return (write(2, "Error\nmlx_init failed\n", 20), 1);
	mrt_ctx.img = mlx_new_image(mrt_ctx.mlx, WIN_W, WIN_H);
	if (!mrt_ctx.img)
		return (write(2, "Error\nimage creation failed\n", 28), 1);
	if (mlx_image_to_window(mrt_ctx.mlx, mrt_ctx.img, 0, 0) < 0)
		return (write(2, "Error\nimage to window failed\n", 30), 1);
//	clear_image(mrt_ctx.img, 0x000000FF);
	draw_test_gradient(mrt_ctx.img);
	mlx_key_hook(mrt_ctx.mlx, on_key, &mrt_ctx);
	mlx_close_hook(mrt_ctx.mlx, (mlx_closefunc)NULL, NULL); // opcional
	mlx_loop(mrt_ctx.mlx);
	mlx_terminate(mrt_ctx.mlx);
	return 0;
}
