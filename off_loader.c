
#include "off_loader.h"

bool big_off_ready = false;
bool hdr_line_ready = false;

bool error_flag = false;

bool skip_new_line = true;

uint32_t verts_registred = 0, faces_registred = 0;

// The number of vertices, faces and edges
uint32_t verts, faces, edges;

// Mesh
off_file mesh;
vert_colored *verts_store;
tri_colored *tris_store;

char *skip_trash(char *buffer) {
	while ((*buffer) == '\r' || ((*buffer) == '\n' && skip_new_line) || (*buffer) == ' ' || (*buffer) == '\t') buffer++;
	return buffer;
}

char *parse_off_line(char *buffer) {
	buffer = skip_trash(buffer);
	// Case of comment line
	if ((*buffer) == '#') {
		buffer += 1;
		while ((*buffer) != '\n') buffer++;
		buffer = skip_trash(buffer);
		return buffer;
	}
	// Case of big OFF 
	char *off = "OFF";
	if (strncmp(buffer, off, 3) == 0 && !big_off_ready && !hdr_line_ready) {
		big_off_ready = true;
		buffer += 3;
		buffer = skip_trash(buffer);
		return buffer;
	}
	// Case of header line, first line started with number
	if ((*buffer) >= '0' && (*buffer) <= '9' && !hdr_line_ready) {
		skip_new_line = false;
		verts = atoi(buffer);
		while ((*buffer) >= '0' && (*buffer) <= '9') buffer++;
		buffer = skip_trash(buffer);
		if ((*buffer) >= '0' && (*buffer) <= '9') {
			faces = atoi(buffer);
			while ((*buffer) >= '0' && (*buffer) <= '9') buffer++;
			buffer = skip_trash(buffer);
		} else {
			error_flag = true;
			return buffer;
		}
		if ((*buffer) >= '0' && (*buffer) <= '9') {
			edges = atoi(buffer);
			while ((*buffer) >= '0' && (*buffer) <= '9') buffer++;
		}
		hdr_line_ready = true;
		skip_new_line = true;
		// Allocate memory for triangles and vertices
		verts_store = malloc(sizeof(vert_colored) * verts);
		tris_store = malloc(sizeof(tri_colored) * faces);
		memset(verts_store, 0, sizeof(vert_colored) * verts);
		memset(tris_store, 0, sizeof(tri_colored) * faces);
		mesh.n_verts = verts; mesh.n_tris = faces; mesh.n_edges = edges;
		mesh.verts = verts_store;
		mesh.tris = tris_store;
		return buffer;
	}
	// Case of vertex
	if (verts_registred < verts && verts != 0 && (((*buffer) >= '0' && (*buffer) <= '9') || (*buffer) == '.' || (*buffer) == '+' || (*buffer) == '-') && hdr_line_ready) {
		double x, y, z;
		x = atof(buffer);
		while (((*buffer) >= '0' && (*buffer) <= '9') || (*buffer) == '.' || (*buffer) == '+' || (*buffer) == '-') buffer++;
		buffer = skip_trash(buffer);
		y = atof(buffer);
		while (((*buffer) >= '0' && (*buffer) <= '9') || (*buffer) == '.' || (*buffer) == '+' || (*buffer) == '-') buffer++;
		buffer = skip_trash(buffer);
		z = atof(buffer);
		while (((*buffer) >= '0' && (*buffer) <= '9') || (*buffer) == '.' || (*buffer) == '+' || (*buffer) == '-') buffer++;
		verts_store[verts_registred].x = x; verts_store[verts_registred].y = y; verts_store[verts_registred].z = z;
		verts_registred++;
		return buffer;
	}
	// Case of face
	if (((verts_registred == verts) && faces_registred < faces && ((*buffer) >= '0' && (*buffer) <= '9')) && (faces != 0) && hdr_line_ready) {
		uint32_t n, a, b, c;
		n = atoi(buffer);
		while ((*buffer) >= '0' && (*buffer) <= '9') buffer++;
		buffer = skip_trash(buffer);
		// Parse the number of A vertex
		a = atoi(buffer);
		while ((*buffer) >= '0' && (*buffer) <= '9') buffer++;
		buffer = skip_trash(buffer);
		// Parse the number of B vertex
		b = atoi(buffer);
		while ((*buffer) >= '0' && (*buffer) <= '9') buffer++;
		buffer = skip_trash(buffer);
		// Parse the number of C vertex
		c = atoi(buffer);
		while ((*buffer) >= '0' && (*buffer) <= '9') buffer++;
		buffer = skip_trash(buffer);
		while ((*buffer) != '\n') buffer++;
		buffer = skip_trash(buffer);
		tris_store[faces_registred].vert_a = a; tris_store[faces_registred].vert_b = b; tris_store[faces_registred].vert_c = c;
		faces_registred++;
		return buffer;
	}
	return NULL;
}

off_file *load_off(char *path) {
	FILE *off;
	off = fopen(path, "r");
	if (off == NULL) return NULL;
	fseek(off, 0, SEEK_END);
	long int size = ftell(off);
	fseek(off, 0, SEEK_SET);
	// Mllocate memory to contain the OFF
	char *buffer = (char *) malloc(sizeof(char) * (size + 1));
	if (buffer == NULL) return NULL; // Allocation error
	memset(buffer, 0, size);
	// Copy the file into the buffer
	size_t result = fread(buffer, 1, size, off);
	char *line = buffer;
	while (((line = parse_off_line(line)) != NULL) && !error_flag);
	if (error_flag) {
		printf("Error\n");
		return NULL;
	}

	return &mesh;
}

void print_off(off_file *off) {
	printf("\tVertices: %i, Tris: %i, Edges: %i\n", off->n_verts, off->n_tris, off->n_edges);
	for (size_t i = 0; i < off->n_verts; i++)
		printf("\t%f, %f, %f\n", ((vert_colored) off->verts[i]).x, ((vert_colored) off->verts[i]).y, ((vert_colored) off->verts[i]).z);
	for (size_t i = 0; i < off->n_tris; i++)
		printf("\t%i, %i, %i\n", ((tri_colored) off->tris[i]).vert_a, ((tri_colored) off->tris[i]).vert_b, ((tri_colored) off->tris[i]).vert_c);
}