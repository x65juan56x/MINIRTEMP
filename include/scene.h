#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include <stdint.h>
#include "vec3.h"

typedef struct s_ambient {
    float  ratio;   // [0,1]
    t_vec3 color;   // [0,1] per channel
    bool   present; // declarado en archivo
} t_ambient;

typedef struct s_camera {
    t_vec3 pos;
    t_vec3 dir;     // normalized
    float  fov_deg; // (0,180)
    bool   present;
} t_camera;

typedef struct s_light {
    t_vec3 pos;
    float  bright;  // [0,1]
    t_vec3 color;   // [0,1] (mandatorio no usa color, pero lo guardamos)
    bool   present;
} t_light;

typedef enum e_objtype { OBJ_SPHERE, OBJ_PLANE, OBJ_CYLINDER } t_objtype;

typedef struct s_sphere { t_vec3 center; float diameter; t_vec3 color; } t_sphere;
typedef struct s_plane  { t_vec3 point;  t_vec3 normal;  t_vec3 color; } t_plane;
typedef struct s_cyl    { t_vec3 center; t_vec3 axis; float diameter; float height; t_vec3 color; } t_cyl;

typedef struct s_object {
    t_objtype       type;
    union {
        t_sphere sp;
        t_plane  pl;
        t_cyl    cy;
    } u;
    struct s_object *next;
} t_object;

typedef struct s_scene {
    t_ambient ambient;
    t_camera  camera;
    t_light   light;
    t_object *objects;
} t_scene;

void scene_init(t_scene *s);
void scene_free(t_scene *s);
void scene_add_object(t_scene *s, t_object *obj);

#endif // SCENE_H
