
#ifndef H_OFF_LOADER
#define H_OFF_LOADER

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "geom.h"

typedef struct {
	uint32_t n_verts; uint32_t n_tris; uint32_t n_edges;
	vert_colored *verts;
	tri_colored *tris;
} off_file;

bool save_off(off_file *mesh, char *path);

off_file *load_off(char *path);

void print_off(off_file *off);

#endif