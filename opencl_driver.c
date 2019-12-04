
#include "opencl_driver.h"

void list_ocl() {
	int i, j;
	char *value;
	size_t valueSize;
	cl_uint platformCount;
	cl_platform_id *platforms;
	cl_uint deviceCount;
	cl_device_id *devices;
	cl_uint maxComputeUnits;
	// Get all platforms
	clGetPlatformIDs(0, NULL, &platformCount);
	platforms = (cl_platform_id *) malloc(sizeof(cl_platform_id) * platformCount);
	clGetPlatformIDs(platformCount, platforms, NULL);
	printf("------------------------------------------------\r\n");
	for (i = 0; i < platformCount; i++) {
		// Platform Info
		char str[256];
		clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 256, str, NULL);
		printf("%i. Name: %s\r\n", i + 1, str);
		// Get all devices
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
		devices = (cl_device_id *) malloc(sizeof(cl_device_id) * deviceCount);
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);
		// For each device print critical attributes
		for (j = 0; j < deviceCount; j++) {
			// Print device name
			clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
			value = (char *) malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
			printf(" %d. Device: %s\n", j + 1, value);
			free(value);
			// Print hardware device version
			clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
			value = (char*) malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
			printf("  %d.%d Hardware version: %s\n", j + 1, 1, value);
			free(value);
			// Print software driver version
			clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
			value = (char *) malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
			printf("  %d.%d Software version: %s\n", j + 1, 2, value);
			free(value);
			// Print c version supported by compiler for device
			clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
			value = (char*) malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
			printf("  %d.%d OpenCL C version: %s\n", j + 1, 3, value);
			free(value);
			// Print parallel compute units
			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(maxComputeUnits), &maxComputeUnits, NULL);
			printf("  %d.%d Parallel compute units: %d\n", j + 1, 4, maxComputeUnits);
		}
		free(devices);
		printf("------------------------------------------------\r\n");
	}
	free(platforms);
}

void add_test(uint32_t platform, uint32_t dev, uint32_t size) {

}