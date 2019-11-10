
#include "off_loader.h"

off_file *open_off(char *path) {
	FILE *off;
	off = fopen(path, "rb");
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
  if (result != size) return NULL;
  printf("Buffer:\n%s\n", buffer);
}