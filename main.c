
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include "opencl_driver.h"
#include "off_loader.h"

int main(int argc, char const *argv[]) {
	printf("TRI Render\n");
	/* for (int i = 0; i < argc; i++) {
		printf("#%i -> %s\n", i, argv[i]);
	} */
	if (argc == 3 && strcmp(argv[1], "--test_off") == 0) {
		uint32_t path_len = strlen(argv[2]);
		char path[path_len];
		strcpy(path, argv[2]);
		off_file *off = load_off(path);
		if (off != NULL) {
			print_off(off);
			return EXIT_SUCCESS;
		} else {
			printf("OFF Error, NULL\n");
			return EXIT_FAILURE;
		}
	}
	if (argc == 2 && strcmp(argv[1], "--ocl_dev") == 0) {
		list_ocl();
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}