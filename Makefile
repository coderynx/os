# Toolchain
ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-gcc
EMU = qemu-system-i386

# Directories
SRC = src
CONFIG = ./config
BUILD = ./build

# Flags
ASM_FLAGS = -f elf32
CC_DEFINES = -DDEBUG
CC_FLAGS = $(CC_DEFINES) -m32 -std=gnu99 -ffreestanding -Wall -Wextra
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
	@printf "Linking...\n"
	$(LD) $(LD_FLAGS) $^ -o $(TARGET)

# Run
run: all
	@printf "Running...\n"
	$(EMU) -kernel $(TARGET)

debug: all
	@printf "Running...\n"
	$(EMU) -s -S -kernel $(TARGET) &
	$(GDB) -ex "target remote localhost:1234" $(TARGET)

# Assembly
$(BUILD)/%.o : $(SRC)/%.asm
	@printf "Assembling...\n"
	@mkdir -p $(BUILD)
	$(ASM) $(ASM_FLAGS) $< -o $@

# C
$(BUILD)/%.o: $(SRC)/%.c
	@printf "Compiling...\n"
	@mkdir -p $(BUILD)
	$(CC) -I$(SRC) -c $(CC_FLAGS) $< -o $@	

clean:
	@printf "Cleaning...\n"
	rm -rf $(BUILD)/*
