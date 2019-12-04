CC = gcc
CFLAGS = -g
SRCS = main.c geom.h off_loader.h off_loader.c opencl_driver.h opencl_driver.c
BUILD = build/tri.exe
OCL_WIN = "C:\\Windows\\System32\\OpenCL.dll"

all: $(SRCS)
	$(CC) -o $(BUILD) -I. $(OCL_WIN) $(CFLAGS) $(SRCS)

clean:
	rm $(BUILD)