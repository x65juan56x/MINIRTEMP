#include <math.h>
#include <float.h>
#include "renderer.h"
#include "color.h"

static inline float deg2rad(float deg)
{
	// Convierte grados a radianes: rad = deg * PI/180.
	// Útil para transformar el FOV proporcionado en grados a la unidad que
	// usan las funciones trigonométricas (radianes).
	return deg * 0.01745329251994329577f; // PI/180
}

void camera_setup(t_camera* cam, uint32_t w, uint32_t h, float vfov_deg)
{
	// Construye una cámara pinhole simple en el origen mirando hacia -Z.
	// - w, h: tamaño del framebuffer para calcular aspect ratio.
	// - vfov_deg: campo de visión vertical en grados.
	// Calculamos un viewport (plano de imagen) a distancia focal 1 en -Z
	// con dimensiones derivadas del FOV y el aspect ratio.
	const float aspect = (float)w / (float)h;
	const float theta = deg2rad(vfov_deg);
	const float half_h = tanf(theta * 0.5f);
	const float viewport_h = 2.0f * half_h;
	const float viewport_w = aspect * viewport_h;
	const float focal_len = 1.0f;

	cam->origin     = v3(0.0f, 0.0f, 0.0f);
	cam->horizontal = v3(viewport_w, 0.0f, 0.0f);
	cam->vertical   = v3(0.0f, viewport_h, 0.0f);
	// Esquina inferior izquierda del plano de imagen a 1 unidad hacia -Z
	cam->lower_left_corner = v3_sub(v3_sub(v3_sub(cam->origin,
							   v3_mul(cam->horizontal, 0.5f)),
							   v3_mul(cam->vertical,   0.5f)),
							   v3(0.0f, 0.0f, focal_len));
}

uint32_t rgbf_to_u32(t_vec3 c)
{
	// Convierte un color en float [0,1] por canal a un color RGBA de 32 bits.
	// Aplica clamping a [0,1], escala a [0,255], y empaqueta como RGBA en memoria
	// con el helper rgba_u32(r,g,b,a) (a=255 opaco).
	int r = (int)(255.999f * fminf(fmaxf(c.x, 0.0f), 1.0f));
	int g = (int)(255.999f * fminf(fmaxf(c.y, 0.0f), 1.0f));
	int b = (int)(255.999f * fminf(fmaxf(c.z, 0.0f), 1.0f));
	return rgba_u32((uint8_t)r, (uint8_t)g, (uint8_t)b, 255);
}

static inline void put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	// Escribe un color de 32 bits en la posición (x,y) del framebuffer de MLX42.
	// Realiza una comprobación de límites y direcciona linealmente el buffer
	// como un array de uint32_t de tamaño width*height.
	if ((unsigned)x >= img->width || (unsigned)y >= img->height)
		return;
	((uint32_t*)img->pixels)[(size_t)y * img->width + (size_t)x] = color;
}

void draw_background(mlx_image_t *img)
{
	// Renderiza un fondo “sky” con un gradiente (blanco->azul) usando rayos de una cámara pinhole.
	// Para cada píxel (x,y):
	//  - Calcula coordenadas normalizadas u,v del viewport.
	//  - Construye un rayo desde el origen de la cámara hacia el punto del plano de imagen.
	//  - Normaliza la dirección y usa su componente y para mezclar entre blanco y azul.
	//  - Escribe el color resultante en el framebuffer.
	t_camera	cam;
	int			y;
	int			x;

	camera_setup(&cam, img->width, img->height, 70.0f);
	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			float u = (float)x / (float)(img->width  - 1);
			float v = 1.0f - (float)y / (float)(img->height - 1); // invertimos para que arriba sea "cielo"

			t_vec3 dir = v3_add(cam.lower_left_corner,
							v3_add(v3_mul(cam.horizontal, u),
								   v3_mul(cam.vertical, v)));
			dir = v3_sub(dir, cam.origin);
			dir = v3_norm(dir);

			float t = 0.5f * (dir.y + 1.0f); // mapear [-1,1] a [0,1]
			t_vec3 white = v3(1.0f, 1.0f, 1.0f);
			t_vec3 sky   = v3(0.5f, 0.7f, 1.0f);
			t_vec3 col   = v3_add(v3_mul(white, (1.0f - t)), v3_mul(sky, t));

			put_pixel(img, x, y, rgbf_to_u32(col));
			x++;
		}
		y++;
	}
}
