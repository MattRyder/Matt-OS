CFLAGS= -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs

#Build Directory for .o and .bin
BUILD_DIR = build

#Build Directory for core objects
BUILD_COMMON = $(BUILD_DIR)/common
BUILD_INTERRUPTS = $(BUILD_DIR)/interrupts
K_OUTPUT = kernel.bin

ALL_OBJECTS = kernel.o loader.o  \
	      common.o monitor.o string.o \
	      descriptor_tables.o isr.o interrupt.o flush_tables.o

STD_OBJECTS = $(BUILD_DIR)/kernel.o $(BUILD_DIR)/loader.o
INTERRUPT_OBJECTS = $(BUILD_INTERRUPTS)/descriptor_tables.o $(BUILD_INTERRUPTS)/isr.o $(BUILD_INTERRUPTS)/interrupt.o $(BUILD_INTERRUPTS)/flush_tables.o
COMMON_OBJECTS = $(BUILD_COMMON)/common.o  $(BUILD_COMMON)/monitor.o $(BUILD_COMMON)/string.o

all: $(ALL_OBJECTS)
	ld -T linker.ld -o $(K_OUTPUT) $(STD_OBJECTS) $(COMMON_OBJECTS) $(INTERRUPT_OBJECTS)
	mv $(K_OUTPUT) $(BUILD_DIR)/scratch/$(K_OUTPUT)

run: all
	qemu -kernel $(BUILD_DIR)/scratch/$(K_OUTPUT)

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

string.o:
	cc -c $(CFLAGS) common/string.c
	mv string.o $(BUILD_COMMON)/string.o

descriptor_tables.o:
	cc -c $(CFLAGS) interrupts/descriptor_tables.c
	mv descriptor_tables.o $(BUILD_INTERRUPTS)/descriptor_tables.o

isr.o:
	cc -c $(CFLAGS) interrupts/isr.c
	mv isr.o $(BUILD_INTERRUPTS)/isr.o

interrupt.o:
	nasm -f elf -o interrupt.o ASM/interrupt.s
	mv interrupt.o $(BUILD_INTERRUPTS)/interrupt.o

flush_tables.o:
	nasm -f elf -o flush_tables.o ASM/flush_tables.s
	mv flush_tables.o $(BUILD_INTERRUPTS)/flush_tables.o

clean:
	rm -rf --verbose $(STD_OBJECTS) $(COMMON_OBJECTS) $(INTERRUPT_OBJECTS) \
    $(BUILD_DIR)/$(K_OUTPUT) $(BUILD_DIR)/scratch/$(K_OUTPUT)
