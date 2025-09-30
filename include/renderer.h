#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "vec3.h"
#include "ray.h"
#include "MLX42/MLX42.h"

typedef struct s_rcamera {
	t_vec3 origin;
	t_vec3 horizontal;
	t_vec3 vertical;
	t_vec3 lower_left_corner;
} t_rcamera;

void camera_setup(t_rcamera* cam, uint32_t w, uint32_t h, float vfov_deg);
uint32_t	rgbf_to_u32(t_vec3 c);
void		draw_background(mlx_image_t *img);

#endif
