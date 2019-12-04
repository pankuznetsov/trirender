
#ifndef H_OPENCL_DRIVER
#define H_OPENCL_DRIVER

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

void list_ocl();

void add_test(uint32_t platform, uint32_t dev, uint32_t size);

#endif