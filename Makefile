CFLAGS= -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -c -m32
AFLAGS= -f elf
LDFLAGS= -m elf_i386 -s -T linker.ld

CC = cc
ASSEMBLER = nasm
LD = ld

#Build Directory for .o and .bin
BUILD_DIR = build/

# Collect all the src files from the directories
SRC_KERNEL = $(wildcard *.c)
SRC_ASM = $(wildcard ASM/*.s)
SRC_COMMON = $(wildcard common/*.c)
SRC_INTERRUPTS = $(wildcard interrupts/*.c)

ALL_SRC = $(SRC_KERNEL) $(SRC_ASM) $(SRC_COMMON) $(SRC_INTERRUPTS)
BUILD_TARGETS = $(patsubst %.s, %.o, $(patsubst %.c, %.o, $(ALL_SRC)))

OBJECTS = $(notdir $(patsubst %.s, %.o, $(patsubst %.c, %.o, $(ALL_SRC))))
BUILD_OBJECTS = $(foreach OBJECT, $(OBJECTS), $(BUILD_DIR)$(OBJECT))

ALL_OBJ = $(wildcard $(BUILD_DIR)*.o)

K_OUTPUT = kernel.bin

all: $(BUILD_TARGETS)
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)scratch/$(K_OUTPUT) $(BUILD_OBJECTS)

%.o: %.s
	$(ASSEMBLER) $(AFLAGS) -o $(BUILD_DIR)$(@F) $^

%.o: %.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)$(@F) $^

clean:
	rm -rf --verbose $(ALL_OBJ) mattos.img
