CFLAGS= -Wall -nostdlib -nostartfiles -nodefaultlibs

BUILD_DIR = ../build

BUILD_COMMON = $(BUILD_DIR)/common
K_OUTPUT = kernel.bin

STD_OBJECTS = $(BUILD_DIR)/kernel.o $(BUILD_DIR)/loader.o
COMMON_OBJECTS = $(BUILD_COMMON)/common.o  $(BUILD_COMMON)/monitor.o $(BUILD_COMMON)/string.o 

all: kernel.o loader.o common.o monitor.o string.o
	ld -T linker.ld -o $(K_OUTPUT) $(STD_OBJECTS) $(COMMON_OBJECTS)
	mv $(K_OUTPUT) $(BUILD_DIR)/$(K_OUTPUT)


run: all
	qemu -kernel $(BUILD_DIR)/$(K_OUTPUT)

common: common.o monitor.o string.o
kernel: kernel.o
monitor: monitor.o
string: string.o

kernel.o:
	cc $(CFLAGS) -c kernel.c
	mv kernel.o $(BUILD_DIR)/kernel.o

loader.o:
	nasm -f elf -o loader.o loader.s
	mv loader.o $(BUILD_DIR)/loader.o

common.o:
	cc -c $(CFLAGS) common/common.c
	mv common.o $(BUILD_COMMON)/common.o

monitor.o:
	cc -c $(CFLAGS) common/monitor.c
	mv monitor.o $(BUILD_COMMON)/monitor.o

string.o:
	cc -c $(CFLAGS) string/string.c
	mv string.o $(BUILD_COMMON)/string.o

clean:
	rm -rf $(STD_OBJECTS) $(COMMON_OBJECTS) $(BUILD_DIR)/$(K_OUTPUT)
