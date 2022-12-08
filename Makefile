ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-gcc

# sources
SRC = src

# objects
OBJ = ./build
CONFIG = ./config

MKDIR= mkdir -p
CP = cp -f
DEFINES=

# assembler flags
ASM_FLAGS = -f elf32
# compiler flags
CC_FLAGS = $(INCLUDE) $(DEFINES) -m32 -std=gnu99 -ffreestanding -Wall -Wextra
# linker flags, for linker add linker.ld file too
LD_FLAGS = -T $(CONFIG)/linker.ld -nostdlib

# target file to create in linking
TARGET=$(OUT)/kernel.bin

SOURCES := $(wildcard $(SRC)/*.c)
ASM_SOURCES := $(wildcard $(SRC)/*.asm)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
ASM_OBJECTS := $(patsubst $(SRC)/%.asm, $(OBJ)/%.o, $(ASM_SOURCES))

all: $(ASM_OBJECTS) $(OBJECTS)
	@printf "[ linking... ]\n"
	$(LD) $(LD_FLAGS) $^ -o $(TARGET)
	@printf "\n[ Running QEMU... ]\n"
	qemu-system-i386 -kernel out/Terminal.bin

$(OBJ)/%.o : $(OBJ)/%.o $(SRC)/%.asm
	@printf "[ assembling... ]\n"
	@mkdir -p $(OBJ)
	$(ASM) $(ASM_FLAGS) $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	@printf "[ compiling... ]\n"
	@mkdir -p $(OBJ)
	$(CC) -I$(SRC) -c $(CC_FLAGS) $< -o $@	

clean:
	rm -rf $(OBJ)/*
