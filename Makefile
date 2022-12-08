# Toolchain
ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-gcc

# Directories
SRC = src
CONFIG = ./config
BUILD = ./build

# Flags
ASM_FLAGS = -f elf32
CC_DEFINES = 
CC_FLAGS = $(INCLUDE) $(CC_DEFINES) -m32 -std=gnu99 -ffreestanding -Wall -Wextra
LD_FLAGS = -T $(CONFIG)/linker.ld -nostdlib

# Final output file
TARGET=$(BUILD)/kernel.bin

# C Source and object files
SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SOURCES))

# Assembly Source and object files
ASM_SOURCES := $(wildcard $(SRC)/*.asm)
ASM_OBJECTS := $(patsubst $(SRC)/%.asm, $(BUILD)/%.o, $(ASM_SOURCES))

# Linking and running
all: $(ASM_OBJECTS) $(OBJECTS)
	@printf "[ linking... ]\n"
	$(LD) $(LD_FLAGS) $^ -o $(TARGET)
	@printf "\n[ Running QEMU... ]\n"
	qemu-system-i386 -kernel $(TARGET)

# Assembly
$(BUILD)/%.o : $(BUILD)/%.o $(SRC)/%.asm
	@printf "[ assembling... ]\n"
	@mkdir -p $(BUILD)
	$(ASM) $(ASM_FLAGS) $< -o $@

# C
$(BUILD)/%.o: $(SRC)/%.c
	@printf "[ compiling... ]\n"
	@mkdir -p $(BUILD)
	$(CC) -I$(SRC) -c $(CC_FLAGS) $< -o $@	

clean:
	rm -rf $(BUILD)/*
