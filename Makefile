CFLAGS= -Wall -nostdlib -nostartfiles -nodefaultlibs

#Build Directory for .o and .bin
BUILD_DIR = build

#Build Directory for core objects
BUILD_COMMON = $(BUILD_DIR)/common
K_OUTPUT = kernel.bin

STD_OBJECTS = $(BUILD_DIR)/kernel.o $(BUILD_DIR)/loader.o $(BUILD_DIR)/gdt_flush.o
COMMON_OBJECTS = $(BUILD_COMMON)/common.o  $(BUILD_COMMON)/monitor.o $(BUILD_COMMON)/gdt.o

all: kernel.o loader.o common.o monitor.o gdt.o gdt_flush.o
	ld -T linker.ld -o $(K_OUTPUT) $(STD_OBJECTS) $(COMMON_OBJECTS)
	mv $(K_OUTPUT) $(BUILD_DIR)/$(K_OUTPUT)


run: all
	qemu -kernel $(BUILD_DIR)/$(K_OUTPUT)

kernel.o:
	cc $(CFLAGS) -c kernel.c
	mv kernel.o $(BUILD_DIR)/kernel.o

loader.o:
	nasm -f elf -o loader.o ASM/loader.s
	mv loader.o $(BUILD_DIR)/loader.o

common.o:
	cc -c $(CFLAGS) common/common.c
	mv common.o $(BUILD_COMMON)/common.o

monitor.o:
	cc -c $(CFLAGS) common/monitor.c
	mv monitor.o $(BUILD_COMMON)/monitor.o

gdt.o:
	cc -c $(CFLAGS) common/gdt.c
	mv gdt.o $(BUILD_COMMON)/gdt.o

gdt_flush.o:
	nasm -f elf -o gdt_flush.o ASM/gdt_flush.s
	mv gdt_flush.o $(BUILD_DIR)/gdt_flush.o

clean:
	rm -rf --verbose $(STD_OBJECTS) $(COMMON_OBJECTS) $(BUILD_DIR)/$(K_OUTPUT)
