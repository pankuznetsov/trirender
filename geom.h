
#ifndef H_GEOM
#define H_GEOM

#include <stdbool.h>
#include <stdint.h>
#include <float.h>

typedef struct {
	float x, y, z;
} vert;

typedef struct {
	float x, y, z, r, g, b, a;
} vert_colored;

typedef struct {
	uint32_t vert_a, vert_b, vert_c;
} tri;

typedef struct {
	uint32_t vert_a, vert_b, vert_c;
	float r, g, b, a;
} tri_colored;

#endif