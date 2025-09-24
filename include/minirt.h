#ifndef MINIRT_H
#define MINIRT_H

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include <stdio.h>
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "renderer.h"

#define WIN_W 800
#define WIN_H 600

// ε para evitar self-intersections (se usará más adelante en ray tracing)
#define EPSILON 1e-4f

#endif
