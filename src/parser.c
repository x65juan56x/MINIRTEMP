#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"
#include "../Libft/libft.h"

// Forward decls from utils
char **read_file_lines(const char *path, size_t *out_count);
void free_lines(char **lines, size_t count);
char **split_ws(const char *s);
void free_tokens(char **toks);
bool parse_int_in_range(const char *s, int minv, int maxv, int *out);
bool parse_vec3(const char *s, t_vec3 *out);
bool parse_color_255(const char *s, t_vec3 *out);
bool vec3_is_normalized(t_vec3 v);
bool vec3_components_in_range(t_vec3 v, float minv, float maxv);
bool parse_float(const char *s, float *out);

static t_parse_result parse_fail(int line, const char *msg)
{
    t_parse_result r = { .ok = false, .message = NULL, .line = line };
    size_t n = ft_strlen(msg) + 1;
    r.message = malloc(n);
    if (r.message) ft_memcpy(r.message, msg, n);
    return r;
}

void parse_result_free(t_parse_result *r)
{
    if (r && r->message) { free(r->message); r->message = NULL; }
}

static bool already(bool *flag) { if (*flag) return false; *flag = true; return true; }

static t_parse_result parse_A(char **t, int line, t_scene *S)
{
    // A <ratio> <R,G,B>
    if (t[1] == NULL || t[2] == NULL || t[3] != NULL) return parse_fail(line, "A: formato inválido");
    if (!already(&S->ambient.present)) return parse_fail(line, "A duplicado");
    float ratio; t_vec3 col;
    if (!parse_float(t[1], &ratio)) return parse_fail(line, "A: ratio inválido");
    if (ratio < 0.0f || ratio > 1.0f) return parse_fail(line, "A: ratio fuera de rango [0,1]");
    if (!parse_color_255(t[2], &col)) return parse_fail(line, "A: color inválido (R,G,B 0..255)");
    S->ambient.ratio = ratio; S->ambient.color = col;
    return (t_parse_result){ .ok = true };
}

static t_parse_result parse_C(char **t, int line, t_scene *S)
{
    // C <pos> <dir_norm> <FOV>
    if (!t[1] || !t[2] || !t[3] || t[4]) return parse_fail(line, "C: formato inválido");
    if (!already(&S->camera.present)) return parse_fail(line, "C duplicado");
    t_vec3 pos, dir; float fov;
    if (!parse_vec3(t[1], &pos)) return parse_fail(line, "C: posición inválida");
    if (!parse_vec3(t[2], &dir)) return parse_fail(line, "C: dirección inválida");
    if (!vec3_components_in_range(dir, -1.0f, 1.0f)) return parse_fail(line, "C: dirección fuera de rango [-1,1]");
    if (!vec3_is_normalized(dir)) return parse_fail(line, "C: dirección no normalizada");
    if (!parse_float(t[3], &fov)) return parse_fail(line, "C: FOV inválido");
    if (fov <= 0.0f || fov >= 180.0f) return parse_fail(line, "C: FOV fuera de (0,180)");
    S->camera.pos = pos; S->camera.dir = dir; S->camera.fov_deg = fov;
    return (t_parse_result){ .ok = true };
}

static t_parse_result parse_L(char **t, int line, t_scene *S)
{
    // L <pos> <bright> <R,G,B?>
    if (!t[1] || !t[2] || t[4]) return parse_fail(line, "L: formato inválido");
    if (!already(&S->light.present)) return parse_fail(line, "L duplicado");
    t_vec3 pos; float b; t_vec3 col = v3(1,1,1);
    if (!parse_vec3(t[1], &pos)) return parse_fail(line, "L: posición inválida");
    if (!parse_float(t[2], &b)) return parse_fail(line, "L: brillo inválido");
    if (b < 0.0f || b > 1.0f) return parse_fail(line, "L: brillo fuera de [0,1]");
    if (t[3] && !parse_color_255(t[3], &col)) return parse_fail(line, "L: color inválido");
    S->light.pos = pos; S->light.bright = b; S->light.color = col;
    return (t_parse_result){ .ok = true };
}

static t_parse_result parse_sp(char **t, int line, t_scene *S)
{
    // sp <center> <diameter> <R,G,B>
    if (!t[1] || !t[2] || !t[3] || t[4]) return parse_fail(line, "sp: formato inválido");
    t_vec3 c; float d; t_vec3 col;
    if (!parse_vec3(t[1], &c)) return parse_fail(line, "sp: centro inválido");
    if (!parse_float(t[2], &d) || d <= 0.0f) return parse_fail(line, "sp: diámetro inválido");
    if (!parse_color_255(t[3], &col)) return parse_fail(line, "sp: color inválido");
    t_object *o = malloc(sizeof(*o)); if (!o) return parse_fail(line, "sp: memoria insuficiente");
    o->type = OBJ_SPHERE; o->u.sp = (t_sphere){ .center=c, .diameter=d, .color=col }; o->next = NULL;
    scene_add_object(S, o);
    return (t_parse_result){ .ok = true };
}

static t_parse_result parse_pl(char **t, int line, t_scene *S)
{
    // pl <point> <normal_norm> <R,G,B>
    if (!t[1] || !t[2] || !t[3] || t[4]) return parse_fail(line, "pl: formato inválido");
    t_vec3 p, n, col;
    if (!parse_vec3(t[1], &p)) return parse_fail(line, "pl: punto inválido");
    if (!parse_vec3(t[2], &n)) return parse_fail(line, "pl: normal inválida");
    if (!vec3_components_in_range(n, -1.0f, 1.0f)) return parse_fail(line, "pl: normal fuera de rango [-1,1]");
    if (!vec3_is_normalized(n)) return parse_fail(line, "pl: normal no normalizada");
    if (!parse_color_255(t[3], &col)) return parse_fail(line, "pl: color inválido");
    t_object *o = malloc(sizeof(*o)); if (!o) return parse_fail(line, "pl: memoria insuficiente");
    o->type = OBJ_PLANE; o->u.pl = (t_plane){ .point=p, .normal=n, .color=col }; o->next = NULL;
    scene_add_object(S, o);
    return (t_parse_result){ .ok = true };
}

static t_parse_result parse_cy(char **t, int line, t_scene *S)
{
    // cy <center> <axis_norm> <diameter> <height> <R,G,B>
    if (!t[1] || !t[2] || !t[3] || !t[4] || !t[5] || t[6]) return parse_fail(line, "cy: formato inválido");
    t_vec3 c, axis, col; float d, h;
    if (!parse_vec3(t[1], &c)) return parse_fail(line, "cy: centro inválido");
    if (!parse_vec3(t[2], &axis)) return parse_fail(line, "cy: eje inválido");
    if (!vec3_components_in_range(axis, -1.0f, 1.0f)) return parse_fail(line, "cy: eje fuera de rango [-1,1]");
    if (!vec3_is_normalized(axis)) return parse_fail(line, "cy: eje no normalizado");
    if (!parse_float(t[3], &d) || d <= 0.0f) return parse_fail(line, "cy: diámetro inválido");
    if (!parse_float(t[4], &h) || h <= 0.0f) return parse_fail(line, "cy: altura inválida");
    if (!parse_color_255(t[5], &col)) return parse_fail(line, "cy: color inválido");
    t_object *o = malloc(sizeof(*o)); if (!o) return parse_fail(line, "cy: memoria insuficiente");
    o->type = OBJ_CYLINDER; o->u.cy = (t_cyl){ .center=c, .axis=axis, .diameter=d, .height=h, .color=col }; o->next = NULL;
    scene_add_object(S, o);
    return (t_parse_result){ .ok = true };
}

t_parse_result parse_scene(const char *path, t_scene *out)
{
    // Validar extensión .rt
    size_t plen = ft_strlen(path);
    if (plen < 3 || ft_strncmp(path + plen - 3, ".rt", 3) != 0)
        return parse_fail(0, "El archivo no tiene extensión .rt");
    scene_init(out);
    size_t n = 0; char **lines = read_file_lines(path, &n);
    if (!lines) return parse_fail(0, "No se pudo abrir/leer el archivo");
    t_parse_result res = { .ok = true };
    for (size_t i = 0; i < n; ++i) {
        char *line = lines[i];
    // Trim inicial y comentarios inline (todo lo que sigue a '#')
    size_t a = 0; while (line[a] && (line[a] == ' ' || line[a] == '\t')) a++;
    char *hash = ft_strchr(line + a, '#');
    if (hash) *hash = '\0';
    // Saltar si vacío tras recorte/comment
    if (line[a] == '\0') continue;
        // Split por espacios
        char **toks = split_ws(line + a);
        if (!toks || !toks[0]) { free_tokens(toks); continue; }
        t_parse_result r = { .ok = true };
        if      (ft_strncmp(toks[0], "A", 2)  == 0) r = parse_A(toks, (int)(i+1), out);
        else if (ft_strncmp(toks[0], "C", 2)  == 0) r = parse_C(toks, (int)(i+1), out);
        else if (ft_strncmp(toks[0], "L", 2)  == 0) r = parse_L(toks, (int)(i+1), out);
        else if (ft_strncmp(toks[0], "sp", 3) == 0) r = parse_sp(toks, (int)(i+1), out);
        else if (ft_strncmp(toks[0], "pl", 3) == 0) r = parse_pl(toks, (int)(i+1), out);
        else if (ft_strncmp(toks[0], "cy", 3) == 0) r = parse_cy(toks, (int)(i+1), out);
        else { r = parse_fail((int)(i+1), "Identificador desconocido"); }
        free_tokens(toks);
        if (!r.ok) { res = r; break; }
    }
    if (res.ok) {
        if (!out->ambient.present) res = parse_fail(0, "Falta Ambient (A)");
        else if (!out->camera.present) res = parse_fail(0, "Falta Camera (C)");
        else if (!out->light.present) res = parse_fail(0, "Falta Light (L)");
    }
    if (!res.ok) {
        // On error free objects
        scene_free(out);
    }
    free_lines(lines, n);
    return res;
}
