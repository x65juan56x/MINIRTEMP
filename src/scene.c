#include <stdlib.h>
#include "scene.h"

void scene_init(t_scene *s)
{
    // Inicializa la escena con valores por defecto y flags de presencia en falso.
    // Esto permite validar que A, C, L se declaren exactamente una vez en el parser.
    s->ambient = (t_ambient){ .ratio = 0.0f, .color = v3(0,0,0), .present = false };
    s->camera  = (t_camera){ .pos = v3(0,0,0), .dir = v3(0,0,-1), .fov_deg = 70.0f, .present = false };
    s->light   = (t_light){ .pos = v3(0,0,0), .bright = 0.0f, .color = v3(1,1,1), .present = false };
    s->objects = NULL;
}

void scene_free(t_scene *s)
{
    // Libera la lista enlazada de objetos y deja la escena en estado limpio.
    t_object *it = s->objects;
    while (it) {
        t_object *n = it->next;
        free(it);
        it = n;
    }
    s->objects = NULL;
}

void scene_add_object(t_scene *s, t_object *obj)
{
    // Inserta un objeto al frente de la lista enlazada de la escena.
    // Es O(1) y suficiente para el parser; el orden de dibujo no importa para ray tracing.
    obj->next = s->objects;
    s->objects = obj;
}
