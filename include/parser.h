#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "scene.h"

typedef struct s_parse_result {
    bool  ok;
    char *message; // malloc'd message on failure; NULL on success
    int   line;    // 1-based line number for error; 0 if not applicable
} t_parse_result;

t_parse_result parse_scene(const char *path, t_scene *out);
void           parse_result_free(t_parse_result *r);

// Helpers from parser_utils.c used by parser.c (optional exposure for tests)
bool vec3_components_in_range(t_vec3 v, float minv, float maxv);

#endif // PARSER_H
