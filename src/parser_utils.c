#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "scene.h"
#include "../Libft/libft.h"

// Read entire file using open/read and split into lines (no stdio).
char **read_file_lines(const char *path, size_t *out_count)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
		return NULL;
	size_t cap = 8192; // initial buffer capacity
	size_t len = 0;
	char *buf = (char *)malloc(cap);
	if (!buf) { close(fd); return NULL; }
	while (1) {
		if (len == cap) {
			size_t ncap = cap * 2;
			char *nbuf = (char *)malloc(ncap);
			if (!nbuf) { free(buf); close(fd); return NULL; }
			ft_memcpy(nbuf, buf, len);
			free(buf);
			buf = nbuf; cap = ncap;
		}
		ssize_t r = read(fd, buf + len, cap - len);
		if (r < 0) { free(buf); close(fd); return NULL; }
		if (r == 0) break; // EOF
		len += (size_t)r;
	}
	close(fd);
	// Ensure zero-termination for convenience
	if (len == cap) {
		char *nbuf = (char *)malloc(cap + 1);
		if (!nbuf) { free(buf); return NULL; }
		ft_memcpy(nbuf, buf, len);
		free(buf); buf = nbuf; cap += 1;
	}
	buf[len] = '\0';

	// Count lines
	size_t lines_count = 0;
	for (size_t i = 0; i < len; ++i) if (buf[i] == '\n') lines_count++;
	if (len > 0 && buf[len - 1] != '\n') lines_count++;

	char **lines = (char **)malloc(sizeof(char*) * (lines_count > 0 ? lines_count : 1));
	if (!lines) { free(buf); return NULL; }

	// Split into lines; strip trailing CR/LF
	size_t idx = 0; size_t i = 0;
	while (i < len) {
		size_t start = i;
		while (i < len && buf[i] != '\n') i++;
		size_t end = i; // [start, end)
		// Trim trailing '\r'
		while (end > start && (buf[end - 1] == '\r')) end--;
		size_t L = end - start;
		char *line = (char *)malloc(L + 1);
		if (!line) { // best-effort cleanup of prior allocations
			for (size_t k = 0; k < idx; ++k) free(lines[k]);
			free(lines); free(buf); return NULL;
		}
		if (L) ft_memcpy(line, buf + start, L);
		line[L] = '\0';
		lines[idx++] = line;
		i++; // skip '\n' if present
	}
	free(buf);
	if (out_count) *out_count = idx;
	return lines;
}

void free_lines(char **lines, size_t count)
{
	for (size_t i = 0; i < count; ++i) free(lines[i]);
	free(lines);
}

// Simple space checker (avoid ctype)
static int is_space(char c) { return (c == ' ' || c == '\t'); }

// Split por espacios (uno o más), ignore tokens vacíos; devuelve array NULL-terminated
char **split_ws(const char *s)
{
	size_t n = 0, cap = 8; char **out = (char **)malloc(cap * sizeof(char*)); if (!out) return NULL;
	const char *p = s;
	while (*p) {
		while (*p && is_space(*p)) p++;
		if (!*p) break;
		const char *q = p;
		while (*q && !is_space(*q)) q++;
		size_t L = (size_t)(q - p);
		char *tok = (char *)malloc(L + 1);
		if (!tok) { free(out); return NULL; }
		if (L) ft_memcpy(tok, p, L); tok[L] = '\0';
		if (n + 1 >= cap) {
			size_t ncap = cap * 2; char **tmp = (char **)malloc(ncap * sizeof(char*));
			if (!tmp) { free(tok); free(out); return NULL; }
			ft_memcpy(tmp, out, n * sizeof(char*)); free(out); out = tmp; cap = ncap;
		}
		out[n++] = tok; p = q;
	}
	out[n] = NULL; return out;
}

void free_tokens(char **toks)
{
	if (!toks) return;
	for (size_t i = 0; toks[i]; ++i) free(toks[i]);
	free(toks);
}

// Minimal float parser: [+/-] digits [ '.' digits ]
bool parse_float(const char *s, float *out)
{
	const char *p = s; int sign = 1; double val = 0.0; double frac = 0.0; double div = 1.0;
	if (*p == '+') { p++; }
	else if (*p == '-') { sign = -1; p++; }
	int has_digit = 0;
	while (*p >= '0' && *p <= '9') { val = val * 10.0 + (double)(*p - '0'); p++; has_digit = 1; }
	if (*p == '.') {
		p++;
		while (*p >= '0' && *p <= '9') { frac = frac * 10.0 + (double)(*p - '0'); div *= 10.0; p++; has_digit = 1; }
	}
	if (!has_digit || *p != '\0') return false;
	double res = (double)sign * (val + (div > 1.0 ? frac / div : 0.0));
	*out = (float)res; return true;
}

bool parse_int_in_range(const char *s, int minv, int maxv, int *out)
{
	const char *p = s; int sign = 1; long v = 0; int has_digit = 0;
	if (*p == '+') p++; else if (*p == '-') { sign = -1; p++; }
	while (*p >= '0' && *p <= '9') { v = v * 10 + (long)(*p - '0'); p++; has_digit = 1; }
	if (!has_digit || *p != '\0') return false;
	v *= sign;
	if (v < (long)minv || v > (long)maxv) return false;
	*out = (int)v; return true;
}

bool parse_vec3(const char *s, t_vec3 *out)
{
	// Formato esperado: x,y,z con posibles floats y signos
	char *tmp = ft_strdup(s); if (!tmp) return false;
	char *a = tmp, *b = ft_strchr(tmp, ','); if (!b) { free(tmp); return false; }
	*b++ = '\0'; char *c = ft_strchr(b, ','); if (!c) { free(tmp); return false; }
	*c++ = '\0';
	float x,y,z;
	bool ok = parse_float(a, &x) && parse_float(b, &y) && parse_float(c, &z);
	if (ok) *out = v3(x,y,z);
	free(tmp); return ok;
}

bool parse_color_255(const char *s, t_vec3 *out)
{
	// Formato: R,G,B enteros [0,255]; devolvemos normalizado [0,1]
	char *tmp = ft_strdup(s); if (!tmp) return false;
	char *a = tmp, *b = ft_strchr(tmp, ','); if (!b) { free(tmp); return false; }
	*b++ = '\0'; char *c = ft_strchr(b, ','); if (!c) { free(tmp); return false; }
	*c++ = '\0';
	int r,g,bv;
	bool ok = parse_int_in_range(a, 0, 255, &r) && parse_int_in_range(b, 0, 255, &g) && parse_int_in_range(c, 0, 255, &bv);
	if (ok) *out = v3((float)r/255.0f, (float)g/255.0f, (float)bv/255.0f);
	free(tmp); return ok;
}

bool vec3_is_normalized(t_vec3 v)
{
	// Consideramos normalizado si |len-1| <= 1e-3
	float len2 = v3_len2(v);
	return fabsf(len2 - 1.0f) <= 2e-3f; // tolerancia cuadrática
}

bool vec3_components_in_range(t_vec3 v, float minv, float maxv)
{
	// Verifica que cada componente esté en [minv, maxv].
	return (v.x >= minv && v.x <= maxv) &&
		   (v.y >= minv && v.y <= maxv) &&
		   (v.z >= minv && v.z <= maxv);
}
